#pragma once

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

#include <map>
#include <vector>

class PolygonSetComponent;

class Shader3D : public GameObject
{
public:
	//整理中のため、未実装はコメントアウト中
	enum class MESH_TYPE
	{
		NO_SHADER = -1,						// シェーダーを使わない(外す)
		NMESH_NO_LIGHTING_DIFFONLY_FOG,		// 剛体 : ライトの効果を受けず、ディフューズの色のみで判断するシェーダー(フォグ効果あり)
		NMESH_DIFFUSE_ONLY,					// 剛体 : ディフューズテクスチャの色のみ(反射色はマテリアルの色を参照)
		SKIN4_DIFFUSE_ONLY,					// スキン1_4 :		//
		SKIN8_DIFFUSE_ONLY,					// スキン5_8 :		//
		NMESH_DIFF_SPEC_NORM,				// 剛体 : ディフューズ、スぺキュラとノーマルマップシェーダー(フォグ効果あり)
		NMESH_DIFF_SPEC_NORM_SHADOW,		// 剛体 : ディフューズ、スぺキュラとノーマルマップシェーダー(フォグ効果あり)、影付き

		SKIN4_DIFF_SPEC_NORM,				// スキン1_4 : ディフューズ、スぺキュラとノーマルマップシェーダー
		SKIN8_DIFF_SPEC_NORM,				// スキン5_8 : ディフューズ、スぺキュラとノーマルマップシェーダー
		NMESH_DIFF_SPEC_TOON,				// 剛体 : ディフューズ、スぺキュラ付きトゥーンシェーダー
		
		NMESH_SHADOW_SETUP_NOT_NORMAL,		// 剛体 : 影シェーダーセットアップ用のノーマルマップ無しシェーダー
		NMESH_SHADOW_SETUP_NORMALMAP,		// 剛体 : 影シェーダーセットアップ用のノーマルマップ付きシェーダー
		
		SKIN4_SHADOW_SETUP_NOT_NORMAL,		// スキン1_4 : 影シェーダーセットアップ用のノーマルマップ無しシェーダー
		SKIN4_SHADOW_SETUP_NORMALMAP,		// スキン1_4 : 影シェーダーセットアップ用のノーマルマップ付きシェーダー

		SKIN8_SHADOW_SETUP_NOT_NORMAL,		// スキン5_8 : 影シェーダーセットアップ用のノーマルマップ無しシェーダー
		SKIN8_SHADOW_SETUP_NORMALMAP,		// スキン5_8 : 影シェーダーセットアップ用のノーマルマップ付きシェーダー

		WATER,								// フレネル反射(水)シェーダー
	};
public:
	Shader3D();
	~Shader3D();
	void Update()override;
private:
	void CBufferUpdate();
public:
	void SetUpMirror(int _mirrorNum, VECTOR &_cPosition, VECTOR &_cTarget);
	void MirrorRender(int _mirrorNum);
	void MirrorSet(VECTOR &_position, float _radiusX, float _radiusY);


	/// <summary>
	///  モデルの持つメッシュのタイプを指定する。　(メッシュのタイプ一つであれば)MV1DrawModel、それ以外はMV1DrawTriangleList)
	/// ・基本的にMV1GetTriangleListVertexTypeで送られて来た値をそのまま送れば対応する
	/// もしマテリアルごとにタイプが違うなら、MV1DrawTriangleListで描画する前に送る 
	/// ・描画を終了する(シェーダーを切る)ときはMESH_TYPE::NO_RENDERを設定する。
	/// そうした場合、DxLibのデフォルトシェーダーが適応される
	/// ・※基本的に他で使わないかもしれないので、自身の描画が終わったらNO_RENDERを一回挟むと安全
	/// </summary>
	/// <param name="_type">MESH_TYPE　の指定するメッシュのタイプ</param>
	void SetMeshTypeShader(MESH_TYPE _type);

	void SetShadowSetUpShader(bool _start);

private:
	bool m_loadEnd;
	//シェーダー変数
	struct Vert_Pxcl_Shader
	{
		std::string vertFile;
		int vertex;
		std::string pixlFile;
		int pixcel;

		Vert_Pxcl_Shader() :
			vertex(-1),pixcel(-1)
		{
			vertFile.clear();
			pixlFile.clear();
		}
	};
	std::map<MESH_TYPE, Vert_Pxcl_Shader> m_shader;

	//鏡用変数(後々クラス化予定)
	PolygonSetComponent * m_polygon;
	struct Mirror
	{
		int handle;
		COLOR_U8 diffuse;
		FLOAT4 ScreenPosition[4];
		VECTOR Position[4];
	};
	std::vector<Mirror> m_mirror;
	int m_mirrorNum;

	Sprite_Info m_toonTexture;	//トゥーン用のテクスチャ

	//シャドウマップ用変数
	struct LIGHT_MATRIX
	{
		MATRIX view;
		MATRIX projection;
	};
	LIGHT_MATRIX m_lightMat;
	int m_deptHandle;
	//深度画像取得時のカメラ設定変数
	float m_othroParam;// = 15200.f;
	float m_offsetParam;// = 10000.f;
	float m_farParam;// = 16680.f;
	//バッファハンドル
	int m_cbufferVS;
	int m_cbufferPS;
	// cbufferPS動作確認用 + シェーダーの深度画像の補正値を手動で変更できるように変数を確保
	float m_shadowCorrection;// = 60.f;
	VECTOR m_lightTarget;
public:
	int GetMirrorNum()const { return m_mirrorNum; }

	void SetTargetPosition(VECTOR &_position) { m_lightTarget = _position; }
};
/*
class PolygonSetComponent;

class Shader : public GameObject
{
public:
	enum class MESH_TYPE
	{
		NO_SHADER = -1,	//描画無し
		DIFFUSE_ONLY,
		DIFFUSE_ONLY_TOON,
		SKIN_4_DIFFUSE,	//1頂点に与える影響1～4個メッシュ
		NO_LIGHT_NORMAL,
		NORMAL,			//剛体メッシュ
		//SKIN_4,			//1頂点に与える影響1～4個メッシュ
		//SKIN_8,			//1頂点に与える影響4～8個メッシュ
		NMAP_NORMAL,	//ノーマルマップ付き剛体メッシュ
		NMAP_SKIN_4,	//ノーマルマップ付き1頂点に与える影響1～4個メッシュ
		NMAP_SKIN_8,	//1頂点に与える影響4～8個メッシュ

		MIRRRO,
	};
public:
	Shader(SceneBase * _scene);
	~Shader();
	void Update()override;

	void SetUpMirror(int _mirrorNum, VECTOR &_cPosition, VECTOR &_cTarget);
	void MirrorRender(int _mirrorNum);
	void ShadowSetUp()override;
private://変数
	struct Vert_Pxcl_Shader
	{
		int vertex;
		int pixcel;
	};
	std::map<MESH_TYPE, Vert_Pxcl_Shader> m_shader;

	PolygonSetComponent * m_polygon;

	//鏡用変数(後々クラス化予定)
	struct Mirror
	{
		int handle;
		COLOR_U8 diffuse;
		FLOAT4 ScreenPosition[4];
		VECTOR Position[4];
	};
	std::vector<Mirror> m_mirror;

	int m_mirrorNum;

	Sprite_Info m_toonTexture;	//トゥーン用のテクスチャ
public://Set、Get
	/// <summary>
	///  モデルの持つメッシュのタイプを指定する。　(メッシュのタイプ一つであれば)MV1DrawModel、それ以外はMV1DrawTriangleList)
	/// ・基本的にMV1GetTriangleListVertexTypeで送られて来た値をそのまま送れば対応する
	/// もしマテリアルごとにタイプが違うなら、MV1DrawTriangleListで描画する前に送る 
	/// ・描画を終了する(シェーダーを切る)ときはMESH_TYPE::NO_RENDERを設定する。
	/// そうした場合、DxLibのデフォルトシェーダーが適応される
	/// ・※基本的に他で使わないかもしれないので、自身の描画が終わったらNO_RENDERを一回挟むと安全
	/// </summary>
	/// <param name="_type">MESH_TYPE　の指定するメッシュのタイプ</param>
	void SetMeshTypeShader(MESH_TYPE _type);

	void MirrorSet(VECTOR &_position, float _radiusX, float _radiusY);
	int GetMirrorNum()const { return m_mirrorNum; }
};
*/
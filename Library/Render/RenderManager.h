#pragma once

#include <MyDxLib.h>
#include <map>
#include "Library/GameObject/GameObject.h"
#include "Render3D/Shader3D/Shader3D.h"
#include <functional>

class Render2D;
class Render3D;
class Camera;
class RenderManager
{
public:
	static RenderManager* GetInstance();
	RenderManager();
	~RenderManager();

	void Update();
	void Draw();
	void Release();

private:
	Render2D* m_render2D;
	Render3D* m_render3D;
public:
	//カメラを生成する。成功したらtrue
	bool CreateCamera();
	//カメラを削除する。成功したらtrue
	bool DeleteCamera();
	//テクスチャを追加する。成功したらtrue
	bool AddTexture(std::string _name, Sprite_Info& _sprite, std::function<void()> _func);
	bool RemoveTexture(std::string _name);
	//テキストを追加する。成功したらtrue
	bool AddText(std::string _name, std::function<void()> _func);
	bool RemoveText(std::string _name);
	//モデルを追加する。成功したらtrue
	bool AddMV1Model(std::string _name, int _handler, Shader3D::MESH_TYPE _mesh, Shader3D::MESH_TYPE _shadowMesh, bool _isWaterDraw = false, bool _isTriangleDraw = false);
	//モデルを描画しなくする。削除するわけでは仁野で注意
	bool RemoveMV1Model(std::string _name);
	const Render3D* GetRender3D()const;
	const Camera *GetCamera()const;
};
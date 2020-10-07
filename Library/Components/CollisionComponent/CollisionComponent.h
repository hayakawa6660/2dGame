#pragma once

#include "../ComponentBase.h"

#include <list>

struct Hit_Info
{
	bool hit;
	VECTOR hitPos;
	VECTOR normal;
};
/// <summary>
///当たり判定をセットして使えるようにする。
///当たり判定は各々呼びたいところもあるので、明示的に呼び出せるようにしておく
///一つのオブジェクトで複数当たり判定を付けることもできる
///そうした場合、呼び出した判定を全て行う
/// </summary>
class CollisionComponent : public ComponentBase
{
public:
	CollisionComponent();
	~CollisionComponent();
private:
	void Start()override;
	void Update()override;
	void Draw()override;

public:
	//カプセル判定用構造体
	struct Capsule_Info
	{
		VECTOR topPos;
		VECTOR bottomPos;
		float radius;
	};

	//球判定用構造体
	struct Sphere_Info
	{
		VECTOR centerPos;
		float radius;
	};

	struct Line_Info
	{
		VECTOR topPos;
		VECTOR bottomPos;
	};

private:
	std::list<Capsule_Info> m_capsuleList;		//カプセルの当たり判定のリスト
	std::list<Line_Info> m_lineList;			//線分の当たり判定のリスト
	std::list<Sphere_Info> m_sphereList;		//球体の当たり判定のリスト

	//当たり判定用のモデル
	int m_model;

public:	//実際に当たり判定をしている関数
	/// <summary>
	/// 線分とモデルの当たり判定をする。
	/// </summary>
	/// <param name="_info">相手側の線分の当たり判定のリスト</param>
	bool IsModelToLine(const std::list<Line_Info> &_info);

	/// <summary>
	/// 線分とモデルの当たり判定をする。
	/// </summary>
	/// <param name="_info">相手側の線分の線分の当たり判定のリスト</param>
	Hit_Info GetLineHitInfo(const std::list<Line_Info> &_info);

	/// <summary>
	/// (相手)カプセルと(自)モデルの当たり判定をする。
	/// </summary>
	/// <param name="_info">相手側の線分のカプセルの当たり判定のリスト</param>
	bool IsModelToCapsule(const std::list<Capsule_Info> &_info);

	/// <summary>
	/// (自)カプセルと(相手)モデルの当たり判定をする。
	/// </summary>
	/// <param name="_model">相手側のモデル情報</param>
	bool IsCapsuleToModel(int _model);


	/// <summary>
	/// (相手)球と(自)モデルの当たり判定をする。
	/// </summary>
	/// <param name="_info">相手側の線分のカプセルの当たり判定のリスト</param>
	bool IsModelToSphere(const std::list<Sphere_Info> &_info);

	/// <summary>
	/// (自)球と(相手)モデルの当たり判定をする。
	/// </summary>
	/// <param name="_model">相手側のモデル情報</param>
	bool IsSphereToModel(int _model);

public:
	/// <summary>
	/// カプセルの当たり判定をセットする
	/// </summary>
	/// <param name="_top">先端のpos情報</param>
	/// <param name="_bottom">末端のpos情報</param>
	/// <param name="_radius">半径</param>
	void SetCapsule(const VECTOR &_top, const VECTOR &_bottom, float _radius);

	/// <summary>
	/// 球体の当たり判定をセットする
	/// </summary>
	/// <param name="_centerPos">中心のposition</param>
	/// <param name="_radius">球の半径</param>
	void SetSpere(const VECTOR &_centerPos, float _radius);

	/// <summary>
	/// 線分の当たり判定をセットする
	/// </summary>
	/// <param name="_top">先端のposition</param>
	/// <param name="_bottom">末端のposition</param>
	void SetLine(const VECTOR &_top, const VECTOR &_bottom);

	/// <summary>
	/// 当たり判定用のモデルをセットする
	/// CollisionMesh等がある場合はそちらをセットする
	/// </summary>
	/// <param name="_model">Loadしたモデルのハンドル</param>
	void SetModel(int _model);

	/// <summary>
	/// アニメーションで判定するモデルの場合のセットアップ処理
	/// アニメーションした後の判定をしたい時に使う
	/// </summary>
	void SetUpColModel();

	/// <summary>
	/// セットした線分の情報を取得する
	/// </summary>
	const std::list<Line_Info>		&GetLineInfo()		{ return m_lineList;	}

	/// <summary>
	/// セットしたカプセルの情報を取得する
	/// </summary>
	const std::list<Capsule_Info>	&GetCapsuleInfo()	{ return m_capsuleList; }

	/// <summary>
	/// セットした球体の情報を取得する
	/// </summary>
	const std::list<Sphere_Info>	&GetSphereInfo()	{ return m_sphereList;	}
};
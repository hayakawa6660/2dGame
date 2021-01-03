#pragma once

#include "../ComponentBase.h"
#include <list>
#include <functional>
#include <unordered_map>

struct Hit_Info
{
	std::string name;		//当たったComponentの名前
	GameObject * hitObject;	//当たったComponentの所属しているGameObjectポインタ

	MV1_COLL_RESULT_POLY singlePoly;
	MV1_COLL_RESULT_POLY_DIM dimPoly;
	VECTOR norm;			//当たったオブジェクトとの法線

	Hit_Info() :
		name(""), hitObject(nullptr),
		singlePoly(MV1_COLL_RESULT_POLY()),
		dimPoly(MV1_COLL_RESULT_POLY_DIM()),
		norm(VGet(0, 0, 0))
	{}
};

class CollisionComponent : public ComponentBase
{
public:
	CollisionComponent();
	~CollisionComponent();
private:
	void Start()override;
	void Update()override;
public:
	struct Line_Info
	{
		VECTOR firstPos;
		VECTOR endPos;
		std::string name;
		Line_Info() :
			firstPos(VGet(0, 0, 0)), endPos(VGet(0, 0, 0)), name("")
		{}
		Line_Info(const VECTOR &_firstPos, const VECTOR &_endPos, std::string& _name) :
			firstPos(_firstPos), endPos(_endPos), name(_name)
		{}
	};

	struct Sphere_Info
	{
		VECTOR centerPos;
		float radius;
		std::string name;
		Sphere_Info() :
			centerPos(VGet(0, 0, 0)), radius(0), name("")
		{}
		Sphere_Info(const VECTOR &_centerPos, float _radius, std::string &_name) :
			centerPos(_centerPos), radius(_radius), name(_name)
		{}
	};

	struct Capsule_Info
	{
		VECTOR firstPos;
		VECTOR endPos;
		float radius;
		std::string name;
		Capsule_Info() :
			firstPos(VGet(0, 0, 0)), endPos(VGet(0, 0, 0)),
			radius(0), name("")
		{}
		Capsule_Info(const VECTOR &_firstPos, const VECTOR &_endPos, float _radius, std::string &_name) :
			firstPos(_firstPos), endPos(_endPos),
			radius(_radius), name(_name)
		{}
	};

private:
	bool m_isCollision;		//当たり判定をするかどうか
	int m_model;			//当たり判定をするモデル(最大一つまで)
	std::list<Line_Info>	m_line;		//線分の当たり判定
	std::list<Sphere_Info>	m_sphere;	//球体の当たり判定
	std::list<Capsule_Info> m_capsule;	//カプセルの当たり判定

	bool m_isTrigger;			//当たり判定の押し出し処理をするかどうか
	std::unordered_map<std::string, std::function<void(Hit_Info)>> m_callback;	//当たり判定発生時に呼び出される関数リスト
	std::list<Hit_Info> m_hitList;
public:	//SetFunction
	/// <summary>
	/// 当たり判定用の3Dモデルをセットする
	/// </summary>
	/// <param name="_model">当たり判定で使用するモデルのハンドル</param>
	void SetCollisionModel(int _model);

	/// <summary>
	/// 当たり判定用の線分情報をセットする
	/// </summary>
	/// <param name="_firstPos">線分の始点</param>
	/// <param name="_endPos">線分の終点</param>
	void SetLine(const VECTOR &_firstPos, const VECTOR &_endPos, std::string _name);

	/// <summary>
	/// 当たり判定用の線分情報をセットする
	/// </summary>
	/// <param name="_firstPos">線分の始点</param>
	/// <param name="_endPos">線分の終点</param>
	void SetSphere(const VECTOR &_firstPos, float _radius, std::string _name);

	/// <summary>
	/// 当たり判定用の線分情報をセットする
	/// </summary>
	/// <param name="_firstPos">線分の始点</param>
	/// <param name="_endPos">線分の終点</param>
	/// <param name="_radius">半径</param>
	void SetCapsule(const VECTOR &_centerPos, const VECTOR &_endPos, float _radius, std::string _name);


	/// <summary>
	/// 当たり判定が発生したときに呼ばれる関数をセットする
	/// </summary>
	/// <param name="_eventName">発生するイベントの名前</param>
	/// <param name="_func">呼ばれる関数</param>
	void SetEvent(std::string _eventName, std::function<void(Hit_Info)> _func);
	
	/// <summary>
	/// 当たり判定が発生したときに呼ばれる関数を解放する
	/// </summary>
	/// <param name="_eventName">発生するイベントの名前</param>
	/// <param name="_func">呼ばれる関数</param>
	void RemoveEvent(std::string _eventName);

	void SetIsTrigger(bool _trigger) { m_isTrigger = _trigger; }
public:	//GetFunction
	int GetModel()const { return m_model; }
	const std::list<Line_Info> &GetLineInfo() { return m_line; }
	const std::list<Sphere_Info> &GetSphereInfo() { return m_sphere; }
	const std::list<Capsule_Info> &GetCapsuleInfo() { return m_capsule; }
	std::unordered_map<std::string, std::function<void(Hit_Info)>> &GetCallBackFunction() { return m_callback; }
	bool GetIsTrigger()const { return m_isTrigger; }
public:	//CollisionFunction
	/*
	void LineToModel(const std::list<Line_Info> &_info);
	void CapsuleToModel(const std::list<Capsule_Info> &_info);

	//図形同士の当たり判定
	void SphereToSpere(const std::list<Sphere_Info>& _info);
	*/

	void LineToModel(CollisionComponent * _p);
	void CapsuleToModel(CollisionComponent * _p);
	//図形同士の当たり判定
	void SphereToSpere(CollisionComponent * _p);

};
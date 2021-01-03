#pragma once

#include "../ComponentBase.h"
#include <list>
#include <functional>
#include <unordered_map>

struct Hit_Info
{
	std::string name;		//��������Component�̖��O
	GameObject * hitObject;	//��������Component�̏������Ă���GameObject�|�C���^

	MV1_COLL_RESULT_POLY singlePoly;
	MV1_COLL_RESULT_POLY_DIM dimPoly;
	VECTOR norm;			//���������I�u�W�F�N�g�Ƃ̖@��

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
	bool m_isCollision;		//�����蔻������邩�ǂ���
	int m_model;			//�����蔻������郂�f��(�ő��܂�)
	std::list<Line_Info>	m_line;		//�����̓����蔻��
	std::list<Sphere_Info>	m_sphere;	//���̂̓����蔻��
	std::list<Capsule_Info> m_capsule;	//�J�v�Z���̓����蔻��

	bool m_isTrigger;			//�����蔻��̉����o�����������邩�ǂ���
	std::unordered_map<std::string, std::function<void(Hit_Info)>> m_callback;	//�����蔻�蔭�����ɌĂяo�����֐����X�g
	std::list<Hit_Info> m_hitList;
public:	//SetFunction
	/// <summary>
	/// �����蔻��p��3D���f�����Z�b�g����
	/// </summary>
	/// <param name="_model">�����蔻��Ŏg�p���郂�f���̃n���h��</param>
	void SetCollisionModel(int _model);

	/// <summary>
	/// �����蔻��p�̐��������Z�b�g����
	/// </summary>
	/// <param name="_firstPos">�����̎n�_</param>
	/// <param name="_endPos">�����̏I�_</param>
	void SetLine(const VECTOR &_firstPos, const VECTOR &_endPos, std::string _name);

	/// <summary>
	/// �����蔻��p�̐��������Z�b�g����
	/// </summary>
	/// <param name="_firstPos">�����̎n�_</param>
	/// <param name="_endPos">�����̏I�_</param>
	void SetSphere(const VECTOR &_firstPos, float _radius, std::string _name);

	/// <summary>
	/// �����蔻��p�̐��������Z�b�g����
	/// </summary>
	/// <param name="_firstPos">�����̎n�_</param>
	/// <param name="_endPos">�����̏I�_</param>
	/// <param name="_radius">���a</param>
	void SetCapsule(const VECTOR &_centerPos, const VECTOR &_endPos, float _radius, std::string _name);


	/// <summary>
	/// �����蔻�肪���������Ƃ��ɌĂ΂��֐����Z�b�g����
	/// </summary>
	/// <param name="_eventName">��������C�x���g�̖��O</param>
	/// <param name="_func">�Ă΂��֐�</param>
	void SetEvent(std::string _eventName, std::function<void(Hit_Info)> _func);
	
	/// <summary>
	/// �����蔻�肪���������Ƃ��ɌĂ΂��֐����������
	/// </summary>
	/// <param name="_eventName">��������C�x���g�̖��O</param>
	/// <param name="_func">�Ă΂��֐�</param>
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

	//�}�`���m�̓����蔻��
	void SphereToSpere(const std::list<Sphere_Info>& _info);
	*/

	void LineToModel(CollisionComponent * _p);
	void CapsuleToModel(CollisionComponent * _p);
	//�}�`���m�̓����蔻��
	void SphereToSpere(CollisionComponent * _p);

};
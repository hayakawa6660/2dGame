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
///�����蔻����Z�b�g���Ďg����悤�ɂ���B
///�����蔻��͊e�X�Ăт����Ƃ��������̂ŁA�����I�ɌĂяo����悤�ɂ��Ă���
///��̃I�u�W�F�N�g�ŕ��������蔻���t���邱�Ƃ��ł���
///���������ꍇ�A�Ăяo���������S�čs��
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
	//�J�v�Z������p�\����
	struct Capsule_Info
	{
		VECTOR topPos;
		VECTOR bottomPos;
		float radius;
	};

	//������p�\����
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
	std::list<Capsule_Info> m_capsuleList;		//�J�v�Z���̓����蔻��̃��X�g
	std::list<Line_Info> m_lineList;			//�����̓����蔻��̃��X�g
	std::list<Sphere_Info> m_sphereList;		//���̂̓����蔻��̃��X�g

	//�����蔻��p�̃��f��
	int m_model;

public:	//���ۂɓ����蔻������Ă���֐�
	/// <summary>
	/// �����ƃ��f���̓����蔻�������B
	/// </summary>
	/// <param name="_info">���葤�̐����̓����蔻��̃��X�g</param>
	bool IsModelToLine(const std::list<Line_Info> &_info);

	/// <summary>
	/// �����ƃ��f���̓����蔻�������B
	/// </summary>
	/// <param name="_info">���葤�̐����̐����̓����蔻��̃��X�g</param>
	Hit_Info GetLineHitInfo(const std::list<Line_Info> &_info);

	/// <summary>
	/// (����)�J�v�Z����(��)���f���̓����蔻�������B
	/// </summary>
	/// <param name="_info">���葤�̐����̃J�v�Z���̓����蔻��̃��X�g</param>
	bool IsModelToCapsule(const std::list<Capsule_Info> &_info);

	/// <summary>
	/// (��)�J�v�Z����(����)���f���̓����蔻�������B
	/// </summary>
	/// <param name="_model">���葤�̃��f�����</param>
	bool IsCapsuleToModel(int _model);


	/// <summary>
	/// (����)����(��)���f���̓����蔻�������B
	/// </summary>
	/// <param name="_info">���葤�̐����̃J�v�Z���̓����蔻��̃��X�g</param>
	bool IsModelToSphere(const std::list<Sphere_Info> &_info);

	/// <summary>
	/// (��)����(����)���f���̓����蔻�������B
	/// </summary>
	/// <param name="_model">���葤�̃��f�����</param>
	bool IsSphereToModel(int _model);

public:
	/// <summary>
	/// �J�v�Z���̓����蔻����Z�b�g����
	/// </summary>
	/// <param name="_top">��[��pos���</param>
	/// <param name="_bottom">���[��pos���</param>
	/// <param name="_radius">���a</param>
	void SetCapsule(const VECTOR &_top, const VECTOR &_bottom, float _radius);

	/// <summary>
	/// ���̂̓����蔻����Z�b�g����
	/// </summary>
	/// <param name="_centerPos">���S��position</param>
	/// <param name="_radius">���̔��a</param>
	void SetSpere(const VECTOR &_centerPos, float _radius);

	/// <summary>
	/// �����̓����蔻����Z�b�g����
	/// </summary>
	/// <param name="_top">��[��position</param>
	/// <param name="_bottom">���[��position</param>
	void SetLine(const VECTOR &_top, const VECTOR &_bottom);

	/// <summary>
	/// �����蔻��p�̃��f�����Z�b�g����
	/// CollisionMesh��������ꍇ�͂�������Z�b�g����
	/// </summary>
	/// <param name="_model">Load�������f���̃n���h��</param>
	void SetModel(int _model);

	/// <summary>
	/// �A�j���[�V�����Ŕ��肷�郂�f���̏ꍇ�̃Z�b�g�A�b�v����
	/// �A�j���[�V����������̔�������������Ɏg��
	/// </summary>
	void SetUpColModel();

	/// <summary>
	/// �Z�b�g���������̏����擾����
	/// </summary>
	const std::list<Line_Info>		&GetLineInfo()		{ return m_lineList;	}

	/// <summary>
	/// �Z�b�g�����J�v�Z���̏����擾����
	/// </summary>
	const std::list<Capsule_Info>	&GetCapsuleInfo()	{ return m_capsuleList; }

	/// <summary>
	/// �Z�b�g�������̂̏����擾����
	/// </summary>
	const std::list<Sphere_Info>	&GetSphereInfo()	{ return m_sphereList;	}
};
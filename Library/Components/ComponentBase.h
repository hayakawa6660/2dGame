#pragma once

#include <string>
#include <MyDxLib.h>

class GameObject;

class ComponentBase
{
public:
	ComponentBase() : m_destroy(false), m_priority(100), m_parent(nullptr), m_tag("") {}
	virtual ~ComponentBase() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}

protected:
	std::string m_tag;		//���̃N���X�̖��O
	bool m_destroy;			// �������폜���邩�ۂ�
	int m_priority;			//Update���񂷏���
	GameObject *m_parent;	//���̃R���|�[�l���g�̏�������N���X
public:
	/// <summary>
	/// �����̃C���X�^���X���폜���鎞�ɌĂяo��
	/// �����Update�̑O�ɍ폜�����
	/// </summary>
	void DestroyComponent() { m_destroy = true; }

	/// <summary>
	/// �^�O������
	/// �^�O�͂P�����t���邱�Ƃ��ł��܂�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	void SetTag(std::string _tag) { m_tag = _tag; }

	/// <summary>
	/// �^�O����v����Component���擾����
	/// </summary>
	/// <param name="tag">�^�O</param>
	/// <returns>Component�̃C���X�^���X</returns>
	const std::string &GetTag() { return m_tag; }

	/// <summary>
	/// �C���X�^���X���폜�v������Ă��邩�𒲂ׂ�
	/// ��ɁASceneManager�Ń`�F�b�N���Ă���
	/// </summary>
	/// <returns>�������t���O</returns>
	bool IsDestroy() const { return m_destroy; }

	/// <summary>
	/// ���̃R���|�[�l���g�̏�������N���X��ݒ肷��
	/// </summary>
	/// <param name="_object">�^�O</param>
	void SetObject(GameObject * _obj) { m_parent = _obj; }

	GameObject * GetParent()const { return m_parent; }
};
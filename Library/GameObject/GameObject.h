#pragma once

#include "MyDxLib.h"
#include <list>
#include <string>

//#include "Library/Components/CollisionComponent/CollisionComponent.h"
class ComponentBase;
class SceneBase;

//struct Hit_Info;
struct Hit_Info;
//struct CollisionComponent::Hit_Info;

class GameObject
{
public:
	GameObject() : m_pScene(nullptr), m_destroy(false), m_tag("") {}
	GameObject(SceneBase* scene) : m_pScene(scene), m_destroy(false), m_tag(""),
		m_position(VGet(0, 0, 0)),
		m_rotation(VGet(0, 0, 0)),
		m_scale(VGet(1, 1, 1)),
		m_matrix(MGetIdent())
	{}
	GameObject(SceneBase* scene, std::string tag) : m_pScene(scene), m_destroy(false), m_tag(tag) {}
	GameObject(std::string tag) : m_pScene(nullptr), m_destroy(false), m_tag(tag) {}

	virtual ~GameObject();
	virtual void Start() {}
	virtual void Update() { ComponentUpdate(); }
	virtual void Draw() { ComponentDraw(); }
	virtual void DrawSetUp() {}
	virtual void ShadowSetUp() {}
	void ComponentUpdate();
	void ComponentDraw();
private:
	struct Components_Info
	{
		bool initialize;
		ComponentBase * component;
		int priority;
		Components_Info() : initialize(false), component(nullptr), priority(20) {}
	};
	std::list<Components_Info> m_componentList;
	std::list<Components_Info> m_comUpList;

	bool m_destroy;
	std::string m_tag;     // �^�O
	SceneBase* m_pScene; // ��������V�[��
	GameObject* m_pObject; // �e�̃I�u�W�F�N�g
	bool m_sort;

	static bool Comp(const Components_Info& o1, const Components_Info& o2);

	VECTOR m_position;
	VECTOR m_rotation;
	VECTOR m_scale;
	MATRIX m_matrix;
public:
	/// <summary>
	/// ��������V�[����Ԃ�
	/// </summary>
	/// <returns>��������V�[���̃|�C���^�[</returns>
	SceneBase * GetScene() { return m_pScene; }

	/// <summary>
	/// �e�̃I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g�̃|�C���^�[</returns>
	GameObject* GetParent() const { return m_pObject; }

	/// <summary>
	/// �e�̃I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g�̃|�C���^�[</returns>
	void SetParent(GameObject* _parent) { m_pObject = _parent; }

	/// <summary>
	/// �����̃C���X�^���X���폜���鎞�ɌĂяo��
	/// �����Update�̑O�ɍ폜�����
	/// </summary>
	void DestroyMe() { m_destroy = true; }

	/// <summary>
	/// �C���X�^���X���폜�v������Ă��邩�𒲂ׂ�
	/// ��ɁASceneManager�Ń`�F�b�N���Ă���
	/// </summary>
	/// <returns></returns>
	bool IsDestroy() const { return m_destroy; }

	/// <summary>
	/// �^�O������
	/// �^�O�͂P�����t���邱�Ƃ��ł��܂�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	void SetTag(std::string _tag) { m_tag = _tag; }


	/// <summary>
	/// �^�O���擾����
	/// </summary>
	/// <returns>�ݒ肳��Ă���^�O</returns>
	const std::string& GetTag() const { return m_tag; }


	/// <summary>
	/// �w�肳�ꂽ�^�O�Ɠ�������Ԃ�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	/// <returns>�����ł����true</returns>
	bool IsTag(std::string _tag) const { return m_tag == _tag; }


	/// <summary>
	/// Component���񂷏��Ԃ̃v���C�I���e�B��ݒ肷��
	///	�f�t�H���g��20�ɐݒ肳��Ă���B
	/// ����̐��l�̓��쏇�Ԃ͕ۏ؂��Ă܂���
	/// </summary>
	/// <param name="_com">�N���X</param>
	/// <param name="_tag">�R���|�[�l���g�ɂ����^�O</param>
	/// <param name="_priority">�Z�b�g���������l</param>
	void SetPriority(ComponentBase * _com, std::string _tag, int _priority);

	//�R���|�[�l���g�̒ǉ�
	template<class C>
	C* AddComponent(std::string _tag)
	{
		C* p = new C();
		p->SetTag(_tag);
		p->SetObject(this);
		PushComponent(p);
		return p;
	}
	void PushComponent(ComponentBase * _component);
	ComponentBase* SearchComponent(std::string tag) const;

	template<class C>
	C* GetComponent(std::string _tag)
	{
		ComponentBase* p = SearchComponent(_tag);
		return dynamic_cast<C*>(p);
	}

	const VECTOR &GetPosition() { return m_position; }
	void SetPosition(const VECTOR &_position) { m_position = _position; }

	const VECTOR &GetRotation() { return m_rotation; }
	void SetRotation(const VECTOR &_rotation) { m_rotation = _rotation; }

	const VECTOR &GetScale() { return m_scale; }
	void SetScale(const VECTOR &_scale) { m_scale = _scale; }

	const MATRIX &GetMatrix() { return m_matrix; }
	void SetMatrix(const MATRIX &_matrix) { m_matrix = _matrix; }

	virtual void OnCollision(const Hit_Info &_info) {}
};
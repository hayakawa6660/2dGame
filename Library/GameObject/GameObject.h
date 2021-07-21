#pragma once

#include "MyDxLib.h"
#include <list>
#include <string>

class ComponentBase;
class SceneBase;
struct Hit_Info;

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
	virtual void Load() {}
	virtual void Start() {}
	virtual void Update() { ComponentUpdate(); }
	void ComponentUpdate();
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
	std::string m_tag;     // タグ
	SceneBase* m_pScene; // 所属するシーン
	GameObject* m_pObject; // 親のオブジェクト
	bool m_sort;

	static bool Comp(const Components_Info& o1, const Components_Info& o2);

	VECTOR m_position;
	VECTOR m_rotation;
	VECTOR m_scale;
	MATRIX m_matrix;
public:
	/// <summary>
	/// 所属するシーンを返す
	/// </summary>
	/// <returns>所属するシーンのポインター</returns>
	SceneBase * GetScene() { return m_pScene; }

	/// <summary>
	/// 親のオブジェクトを返す
	/// </summary>
	/// <returns>親オブジェクトのポインター</returns>
	GameObject* GetParent() const { return m_pObject; }

	/// <summary>
	/// 親のオブジェクトを返す
	/// </summary>
	/// <returns>親オブジェクトのポインター</returns>
	void SetParent(GameObject* _parent) { m_pObject = _parent; }

	/// <summary>
	/// 自分のインスタンスを削除する時に呼び出す
	/// 次回のUpdateの前に削除される
	/// </summary>
	void DestroyMe() { m_destroy = true; }

	/// <summary>
	/// インスタンスが削除要求されているかを調べる
	/// 主に、SceneManagerでチェックしている
	/// </summary>
	/// <returns></returns>
	bool IsDestroy() const { return m_destroy; }

	/// <summary>
	/// タグをつける
	/// タグは１つだけ付けることができます
	/// </summary>
	/// <param name="_tag">タグ</param>
	void SetTag(std::string _tag) { m_tag = _tag; }


	/// <summary>
	/// タグを取得する
	/// </summary>
	/// <returns>設定されているタグ</returns>
	const std::string& GetTag() const { return m_tag; }


	/// <summary>
	/// 指定されたタグと同じかを返す
	/// </summary>
	/// <param name="_tag">タグ</param>
	/// <returns>同じであればtrue</returns>
	bool IsTag(std::string _tag) const { return std::hash<std::string>()(m_tag) == std::hash<std::string>()(_tag); }


	/// <summary>
	/// Componentを回す順番のプライオリティを設定する
	///	デフォルトで20に設定されている。
	/// 同一の数値の動作順番は保証してません
	/// </summary>
	/// <param name="_com">クラス</param>
	/// <param name="_tag">コンポーネントにつけたタグ</param>
	/// <param name="_priority">セットしたい数値</param>
	void SetPriority(ComponentBase * _com, std::string _tag, int _priority);

	//コンポーネントの追加
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
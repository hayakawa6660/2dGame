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

protected:
	std::string m_tag;		//このクラスの名前
	bool m_destroy;			// 自分を削除するか否か
	int m_priority;			//Updateを回す順番
	GameObject *m_parent;	//このコンポーネントの所属するクラス
public:
	/// <summary>
	/// 自分のインスタンスを削除する時に呼び出す
	/// 次回のUpdateの前に削除される
	/// </summary>
	void DestroyComponent() { m_destroy = true; }

	/// <summary>
	/// タグをつける
	/// タグは１つだけ付けることができます
	/// </summary>
	/// <param name="_tag">タグ</param>
	void SetTag(std::string _tag) { m_tag = _tag; }

	/// <summary>
	/// タグが一致したComponentを取得する
	/// </summary>
	/// <param name="tag">タグ</param>
	/// <returns>Componentのインスタンス</returns>
	const std::string &GetTag() { return m_tag; }

	/// <summary>
	/// インスタンスが削除要求されているかを調べる
	/// 主に、SceneManagerでチェックしている
	/// </summary>
	/// <returns>消されるフラグ</returns>
	bool IsDestroy() const { return m_destroy; }

	/// <summary>
	/// このコンポーネントの所属するクラスを設定する
	/// </summary>
	/// <param name="_object">タグ</param>
	void SetObject(GameObject * _obj) { m_parent = _obj; }

	GameObject * GetParent()const { return m_parent; }
};
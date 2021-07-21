#pragma once
#include <list>
#include "../GameObject/GameObjectManager.h"

class SceneBase {
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Update() { objectManager.Update(); }
private:
	GameObjectManager objectManager;
public:
	/// <summary>
	/// GameObjectを削除する
	/// </summary>
	/// <param name="obj">GameObjectのインスタンス</param>
	inline void DeleteGameObject(GameObject * obj)
	{
		objectManager.DeleteGameObject(obj);
	}

	/// 	/// <summary>
	/// tagが一致するすべてのGameObjectを抽出する
	/// </summary>
	/// <param name="tag">評価するタグ</param>
	/// <returns>タグが一致したGameObjectのインスタンス</returns>
	inline std::list<GameObject*> FindGameObjects(std::string tag)
	{
		return objectManager.FindGameObjects(tag);
	}

	/// <summary>
	/// 描画のプライオリティを設定する
	/// 数値が少ない順に描画されるので、手前に表示したい時は値を高くする
	/// プライオリティが同じものの順番は保証されない
	/// プライオリティのデフォルトは100です
	/// </summary>
	/// <param name="obj">プライオリティを設定するオブジェクト</param>
	/// <param name="order">描画プライオリティ</param>
	inline void SetDrawOrder(GameObject * _obj, int _order)
	{
		objectManager.SetDrawOrder(_obj, _order);
	}

/// 	/// <summary>
/// GameObjectを生成する
/// ここで生成すると、Update,Drawが呼ばれるようになる
/// </summary>
	template <class C>
	C* CreateGameObject(std::string _tag) {
		C* obj = new C(this);
		obj->SetTag(_tag);
		objectManager.PushGameObject(obj);
		return obj;
	};

	/// <summary>
	/// tagを指定して、GameObjectを検索する
	/// 全オブジェクトから、tagが同じオブジェクトを返します
	/// ただし、最初に見つかったものだけを返します
	/// 見つからなければ、nullptrを返します
	/// </summary>
	template <class C>
	C* FindGameObject(std::string _tag) {
		GameObject* obj = objectManager.FindGameObject(_tag);
		return dynamic_cast<C*>(obj);
	};
};

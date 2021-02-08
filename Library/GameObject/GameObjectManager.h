#pragma once

#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Start();
	void Update();
	void Draw();
	void DrawSetUp();
	void ShadowSetUp();
	/// <summary>
	/// オブジェクトの管理を開始する
	/// </summary>
	/// <param name="obj">登録するGameObject</param>
	void PushGameObject(GameObject* obj);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::list<GameObject*> GetAllObjects() const;

	/// 	/// <summary>
	/// タグが一致したGameObjectを取得する
	/// </summary>
	/// <param name="tag">タグ</param>
	/// <returns>GameObjectのインスタンス</returns>
	GameObject* FindGameObject(std::string tag) const;

	/// <summary>
	/// tagが一致するすべてのGameObjectを抽出する
	/// </summary>
	/// <param name="tag">評価するタグ</param>
	/// <returns>タグが一致したGameObjectのインスタンス</returns>
	std::list<GameObject*> FindGameObjects(std::string tag) const;

	/// <summary>
	/// GameObjectを削除する
	/// </summary>
	/// <param name="obj">GameObjectのインスタンス</param>
	void DeleteGameObject(GameObject* obj);

	/// <summary>
	/// 全てのGameObjectを削除する
	/// </summary>
	void DeleteAllGameObject();

	/// <summary>
	/// 描画のプライオリティを設定する
	/// 数値が少ない順に描画されるので、２Ｄでは奥に表示される
	/// ２Ｄで手前に表示したい時、３Ｄで後に描画したい時は、値を高くする
	/// プライオリティが同じものの順番は保証されない
	/// プライオリティのデフォルトは100です
	/// </summary>
	/// <param name="obj">プライオリティを設定するオブジェクト</param>
	/// <param name="order">描画プライオリティ</param>
	void SetDrawOrder(GameObject* _obj, int _order);

private:
	struct NODE
	{
		int order;
		bool initialized;
		bool loaded;
		GameObject* object;
		NODE() : order(100), object(nullptr), initialized(false), loaded(false) {}
	};
	std::list<NODE> m_objects;     // ここで管理しているGameObjectリスト
	std::list<NODE> m_drawObjects; // 描画用のGameObjectリスト
	std::list<NODE> m_collisionObject;	//autoCollisionに登録されている当たり判定リスト
	bool m_needSort;

	void DeleteFromDrawObjects(GameObject* obj);
	void DeleteFromCollObjects(GameObject* obj);
	static bool Comp(const NODE& o1, const NODE& o2);
};
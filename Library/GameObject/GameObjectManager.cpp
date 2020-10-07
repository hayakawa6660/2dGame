#include "gameObjectManager.h"

GameObjectManager::GameObjectManager()
{
	m_objects.clear();
	m_drawObjects.clear();
	m_drawSort = false;
	m_upSort = false;
}

GameObjectManager::~GameObjectManager()
{
	DeleteAllGameObject();
	m_drawSort = false;
	m_upSort = false;
}

void GameObjectManager::Start()
{
	DeleteAllGameObject();
	m_drawSort = false;
	m_upSort = false;
}

void GameObjectManager::Update()
{
	if (m_upSort)
	{
		m_objects.clear();
		m_objects = m_objects; // Listを全コピー
		m_objects.sort(DrawComp); // 昇順にソート
		m_upSort = false;
	}

	for (auto it = m_objects.begin(); it != m_objects.end();)
	{
		NODE& node = (*it);
		if (!node.initialized)
		{
			node.object->Start();
			node.initialized = true;
		}
		if (node.object->IsDestroy())
		{
			DeleteFromDrawObjects(node.object);
			delete node.object;
			it = m_objects.erase(it);
		}
		else
		{
			node.object->Update();
			it++;
		}
	}
}

void GameObjectManager::ShadowDraw()
{
	for (auto& node : m_drawObjects)
		node.object->ShadowDraw();
}

void GameObjectManager::MirrorDraw()
{
	for (auto& node : m_drawObjects)
		node.object->MirrorDraw();
}

void GameObjectManager::Draw()
{
	if (m_drawSort)
	{
		m_drawObjects.clear();
		m_drawObjects = m_objects; // Listを全コピー
		m_drawObjects.sort(DrawComp); // 昇順にソート
		m_drawSort = false;
	}

	for (auto& node : m_drawObjects)
		node.object->Draw();
}

bool GameObjectManager::DrawComp(const NODE & o1, const NODE & o2)
{
	return o1.drawOrder < o2.drawOrder;
}

bool GameObjectManager::UpComp(const NODE & o1, const NODE & o2)
{
	return o1.upOrder < o2.upOrder;
}

void GameObjectManager::PushGameObject(GameObject * obj)
{
	NODE node;
	node.object = obj;
	m_objects.emplace_back(node);
	m_drawSort = true;
}

std::list<GameObject*> GameObjectManager::GetAllObjects() const
{
	std::list<GameObject*> list;

	list.clear();
	for (auto& node : m_objects)
		list.push_back(node.object);
	return list;
}

GameObject * GameObjectManager::FindGameObject(std::string tag) const
{
	for (auto& node : m_objects) {
		if (node.object->IsTag(tag))
			return node.object;
	}
	return nullptr;
}

std::list<GameObject*> GameObjectManager::FindGameObjects(std::string tag) const
{
	std::list<GameObject*> list;

	list.clear();
	for (auto& node : m_objects) {
		if (node.object->IsTag(tag))
			list.push_back(node.object);
	}
	return list;
}

void GameObjectManager::DeleteGameObject(GameObject * obj)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); ) {
		NODE& node = *it;
		if (node.object == obj) {
			DeleteFromDrawObjects(obj);
			delete node.object;
			m_objects.erase(it);
			return;
		}
		it++;
	}
}

void GameObjectManager::DeleteAllGameObject()
{
	for (auto it = m_objects.begin(); it != m_objects.end();) {
		delete (*it).object;
		it = m_objects.erase(it);
	}
	for (auto it = m_drawObjects.begin(); it != m_drawObjects.end();) {
		it = m_drawObjects.erase(it);
	}
}

void GameObjectManager::SetDrawOrder(GameObject * _obj, int _order)
{
	for (auto& node : m_objects) {
		if (node.object == _obj) {
			node.drawOrder = _order;
			m_drawSort = true;
		}
	}
}

void GameObjectManager::SetUpdateOrder(GameObject * _obj, int _order)
{
	for (auto& node : m_objects) {
		if (node.object == _obj) {
			node.upOrder = _order;
			m_upSort = true;
		}
	}
}

void GameObjectManager::DeleteFromDrawObjects(GameObject * obj)
{
	for (auto it = m_drawObjects.begin(); it != m_drawObjects.end(); ) {
		NODE& node = *it;
		if (node.object == obj) {
			it = m_drawObjects.erase(it);
			return;
		}
		it++;
	}
}

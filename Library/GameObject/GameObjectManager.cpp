#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
	m_objects.clear();
	m_drawObjects.clear();
	m_needSort = false;
}

GameObjectManager::~GameObjectManager()
{
	DeleteAllGameObject();
	m_needSort = false;
}

void GameObjectManager::Start()
{
	DeleteAllGameObject();
	m_needSort = false;
}

void GameObjectManager::Update()
{
	for (auto it = m_objects.begin(); it != m_objects.end(); ) {
		NODE& node = (*it);
		if (!node.loaded)
		{
			node.object->Load();
			node.loaded = true;
			it++;
		}
		else if (!node.initialized) {
			node.object->Start();
			node.initialized = true;
			it++;
		}
		else if (node.object->IsDestroy()) {
			DeleteFromDrawObjects(node.object);
			DeleteFromCollObjects(node.object);
			delete node.object;
			it = m_objects.erase(it);
		}
		else {
			node.object->Update();
			it++;
		}
	}
}

bool GameObjectManager::Comp(const NODE & o1, const NODE & o2)
{
	return o1.order < o2.order;
}

void GameObjectManager::PushGameObject(GameObject * obj)
{
	NODE node;
	node.object = obj;
	m_objects.emplace_back(node);
	m_needSort = true;
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
	for (auto it = m_objects.begin(); it != m_objects.end(); ) {
		delete (*it).object;
		it = m_objects.erase(it);
	}
	for (auto it = m_drawObjects.begin(); it != m_drawObjects.end(); ) {
		it = m_drawObjects.erase(it);
	}
}

void GameObjectManager::SetDrawOrder(GameObject * _obj, int _order)
{
	for (auto& node : m_objects) {
		if (node.object == _obj) {
			node.order = _order;
			m_needSort = true;
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

void GameObjectManager::DeleteFromCollObjects(GameObject * obj)
{
	for (auto it = m_collisionObject.begin(); it != m_collisionObject.end(); ) {
		NODE& node = *it;
		if (node.object == obj) {
			it = m_collisionObject.erase(it);
			return;
		}
		it++;
	}
}

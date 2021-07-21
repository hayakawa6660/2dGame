#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Components/ComponentBase.h"

GameObject::~GameObject()
{
	for (auto it = m_componentList.begin(); it != m_componentList.end();)
	{
		delete (*it).component;
		it = m_componentList.erase(it);
	}
	for (auto it = m_comUpList.begin(); it != m_comUpList.end();)
	{
		it = m_comUpList.erase(it);
	}
}

void GameObject::ComponentUpdate()
{
	if (m_sort)
	{
		m_comUpList.clear();
		m_comUpList = m_componentList; // List��S�R�s�[
		m_comUpList.sort(Comp); // �����Ƀ\�[�g
		m_sort = false;
	}

	for (auto it = m_comUpList.begin(); it != m_comUpList.end();)
	{
		Components_Info &info = (*it);
		if (!info.initialize)
		{
			info.component->Start();
			info.initialize = true;
			it++;
		}
		else if (info.component->IsDestroy())
		{
			delete info.component;
			it = m_componentList.erase(it);
		}
		else
		{
			info.component->Update();
			it++;
		}
	}
}

bool GameObject::Comp(const Components_Info & o1, const Components_Info & o2)
{
	return o1.priority < o2.priority;
}

void GameObject::SetPriority(ComponentBase * _com, std::string _tag, int _priority)
{
	for (auto& node : m_componentList)
	{
		//�������ׂ̈�std::hash���g��
		if (node.component == _com && std::hash<std::string>()(node.component->GetTag()) == std::hash<std::string>()(_tag))
		{
			node.priority = _priority;
			m_sort = true;
		}
	}
}

void GameObject::PushComponent(ComponentBase * _component)
{
	Components_Info info;
	info.component = _component;
	m_componentList.emplace_back(info);
	m_sort = true;
}

ComponentBase * GameObject::SearchComponent(std::string tag) const
{
	for (auto& it : m_componentList)
	{
		if (std::hash<std::string>()(it.component->GetTag()) == std::hash<std::string>()(tag))
			return it.component;
	}
	return nullptr;
}
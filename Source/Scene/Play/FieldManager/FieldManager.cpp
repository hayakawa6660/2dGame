#include "FieldManager.h"
//Scenes
#include "../PlayScene.h"
#include "NormalFloor/NormalFloor.h"

FieldManager::FieldManager(SceneBase * _scene) :
	GameObject(_scene), m_listDestroy(false)
{
	m_fieldList.clear();
	for (int i = 0; i < 800; i += 30)
	{
		std::string str = "NF_" + std::to_string(i / 30);
		NormalFloor* p = GameObject::GetScene()->CreateGameObject<NormalFloor>(str);
		VECTOR pos = VGet((float)i, 500.f, 0);
		p->SetStatus(pos, 15.f, 15.f, 15.f, 15.f);
		p->SetParent(this);
		m_fieldList.emplace_back(p);
	}
}

FieldManager::~FieldManager()
{
	m_fieldList.clear();	//自動デリートされるのでクリアのみ
}

void FieldManager::Update()
{
	//フィールドが消えた場合その要素だけを消す。
	if (m_listDestroy)
	{
		m_listDestroy = false;
		for (auto & it = m_fieldList.begin(); it != m_fieldList.end();)
		{
			if ((*it)->IsDestroy())
			{
				it = m_fieldList.erase(it);
			}
		}
	}
}

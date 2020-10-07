#include "SoundManager.h"
#include "Sounds/Sounds.h"

#include "../../../Library/Common/commonObjects.h"
#include "Sounds/Sounds.h"

SoundManager::SoundManager(SceneBase * _scene) :
	GameObject(nullptr)
{
	m_soundList.clear();

	Sounds * p = CommonObjects::GetInstance()->CreateGameObject<Sounds>("CommonSound");
	m_soundList.emplace_back(p);
}

SoundManager::~SoundManager()
{
	m_soundList.clear();
}

void SoundManager::Update()
{
}

Sounds*  SoundManager::CreateSceneSound()
{
	Sounds * p = CommonObjects::GetInstance()->CreateGameObject<Sounds>("SceneSound");
	m_soundList.emplace_back(p);
	return p;
}

void SoundManager::DestroySceneSound()
{
	Sounds * p = CommonObjects::GetInstance()->FindGameObject<Sounds>("SceneSound");
	if (p != nullptr)
		p->DestroyMe();
	for (auto it = m_soundList.begin(); it != m_soundList.end();)
	{
		if ((*it)->IsDestroy())
		{
			it = m_soundList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void SoundManager::AllStop()
{
	for (auto & it : m_soundList)
		it->AllStop();
}

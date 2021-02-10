#include "EnemyManager.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"

EnemyManager::EnemyManager(SceneBase * _scene) :
	GameObject(_scene)
{
	/*
	{
		CompressManager * c = CommonObjects::GetInstance()->FindGameObject<CompressManager>("SceneCompress");
		c->UnCompress("data\\Player.zip", "data\\Player");
	}
	*/
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Load()
{
	/*
	{
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		p->ModelLoad("data\\Player\\gensin_syuzinkou_amb.mv1");
	}
	*/
}

void EnemyManager::Start()
{
	//ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
	//int a = p->GetHandle("data\\Player\\gensin_syuzinkou_amb.mv1");
}

void EnemyManager::Update()
{
}

void EnemyManager::Draw()
{
}

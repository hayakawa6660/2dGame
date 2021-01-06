#include "PlayScene.h"
//System
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Library/Common/commonObjects.h"
//Scenes
#include "Player/Player.h"
#include "FieldManager/FieldManager.h"

PlayScene::PlayScene()
{
	SceneBase::CreateGameObject<Player>("Player");
	SceneBase::CreateGameObject<FieldManager>("FieldManager");
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
	if (p->AllLoadEndCheck())
	{
		SceneBase::Update();
	}
}

void PlayScene::Draw()
{
	SceneBase::Draw();
}

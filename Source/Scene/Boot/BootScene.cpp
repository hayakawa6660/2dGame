#include "bootScene.h"
#include "../../../Library/SceneManager/SceneManager.h"
#include <MyDxLib.h>
#include "../../../Library/Common/commonObjects.h"
#include "../../System/ResourceManager/ResourceManager.h"
#include "../../System/ControllerManager/ControllerManager.h"
#include "../../System/DebugManager/DebugManager.h"
#include "../../System/LoadManager/LoadManager.h"
#include "../../System/CsvManager/CsvManager.h"
#include "../../System/EffectManager/EffectManager.h"
#include "../../System/MyEffekseer/MyEffekseer.h"
#include "../../System/FadeManager/FadeManager.h"
#include "../../System/SoundManager/SoundManager.h"
#include "../../System/CacheManager/CacheManager.h"

BootScene::BootScene()
{
	CommonObjects * p = CommonObjects::GetInstance();
	p->CreateGameObject<ResourceManager>("SceneResource");
	p->CreateGameObject<ResourceManager>("SystemResource");
	p->CreateGameObject<ControllerManager>("ControllerManager");
	p->CreateGameObject<DebugManager>("DebugManager");
	p->CreateGameObject<LoadManager>("LoadManager");
	p->CreateGameObject<CsvManager>("CsvManager");
	p->CreateGameObject<MyEffekseer>("MyEffekseer");
	p->CreateGameObject<EffectManager>("EffectManager");
	p->CreateGameObject<SoundManager>("SoundManager");
	p->CreateGameObject<CacheManager>("CacheManager");

	FadeManager * fade = p->CreateGameObject<FadeManager>("FadeManager");
	p->SetDrawOrder(fade, 1000);
	DebugManager * debug = p->FindGameObject<DebugManager>("DebugManager");
	p->SetDrawOrder(debug, 10000);
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	ResourceManager *p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	if (p->AllLoadEndCheck())
	{
		p->ResetLoadSize();
		SceneManager::GetInstance()->ChangeScene("TitleScene"); // 起動が終わったらTitleを表示
	}
}

void BootScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "Boot : 起動中…");
}

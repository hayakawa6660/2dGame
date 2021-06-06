#include "bootScene.h"
#include "Library/SceneManager/SceneManager.h"
#include <MyDxLib.h>
#include "Library/Common/commonObjects.h"
#include "Source/System/ResourceManager/ResourceManager.h"
//#include "Source/System/ControllerManager/ControllerManager.h"
#include "Source/System/DebugManager/DebugManager.h"
#include "Source/System/LoadManager/LoadManager.h"
#include "Source/System/CsvManager/CsvManager.h"
#include "Source/System/EffectManager/EffectManager.h"
#include "Source/System/MyEffekseer/MyEffekseer.h"
#include "Source/System/FadeManager/FadeManager.h"
#include "Source/System/SoundManager/SoundManager.h"
#include "Source/System/CacheManager/CacheManager.h"
#include "Source/System/RenderManager/RenderManager.h"
#include "Source/System/ThreadManager/ThreadManager.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/InputManager/InputManager.h"

//#include "Source/System/KeyboardManager/KeyboardManager.h"

BootScene::BootScene()
{
	CommonObjects * p = CommonObjects::GetInstance();
	p->CreateGameObject<CompressManager>("CompressManager");

	p->CreateGameObject<ResourceManager>("SceneResource");
	p->CreateGameObject<ResourceManager>("SystemResource");
	//p->CreateGameObject<ControllerManager>("ControllerManager");
	p->CreateGameObject<DebugManager>("DebugManager");
	p->CreateGameObject<LoadManager>("LoadManager");
	p->CreateGameObject<CsvManager>("CsvManager");
	p->CreateGameObject<MyEffekseer>("MyEffekseer");
	p->CreateGameObject<EffectManager>("EffectManager");
	p->CreateGameObject<SoundManager>("SoundManager");
	p->CreateGameObject<CacheManager>("CacheManager");
	p->CreateGameObject<RenderManager>("RenderManager");
	p->CreateGameObject<ThreadManager>("ThreadManager");

	FadeManager * fade = p->CreateGameObject<FadeManager>("FadeManager");
	p->SetDrawOrder(fade, 1000);
	DebugManager * debug = p->FindGameObject<DebugManager>("DebugManager");
	p->SetDrawOrder(debug, 10000);

	InputManager * input = p->CreateGameObject<InputManager>("InputManager");
	input->SetKeyBind("ESC", KEY_INPUT_ESCAPE);
	input->SetKeyBind("SPACE", KEY_INPUT_SPACE);
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
	DrawFormatString(0, 0, 0xffffff, "起動中...");
}

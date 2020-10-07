#include "TitleScene.h"
//SceneObject

//System
#include "../../../Library/Common/commonObjects.h"
#include "../../System/FadeManager/FadeManager.h"
#include "../../System/DebugManager/DebugManager.h"

TitleScene::TitleScene()
{
	CommonObjects::GetInstance()->FindGameObject<FadeManager>("FadeManager")->SetFadeLevel(0);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	SceneBase::Update();
#if DEBUG
	int a = 100;
	Debug::DebugPrintf(100, 0, "Title", "%d", a);
#endif
}

void TitleScene::Draw()
{
	SceneBase::ShadowDraw();
	SceneBase::MirrorDraw();
	SceneBase::Draw();
}

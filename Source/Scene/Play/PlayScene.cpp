#include "PlayScene.h"
//#include "PlayState/PlayNewClasses/PlayNewClasses.h"
#include "PlayState/PlayLoad/PlayLoad.h"
#include "Camera/Camera.h"
#include "Library/Common/commonObjects.h"

//Render変更箇所
#include "Library/Render/RenderManager.h"

PlayScene::PlayScene() :
	m_next(nullptr),
	m_current(nullptr)
{
	SetNextState<PlayLoad>("PlayLoad");

	SetFogEnable(TRUE);
	// フォグの色を白色にする
	SetFogColor(150, 150, 255);
	//SetFogColor(255, 50, 50);

	// フォグの開始距離を0、終了距離を1500にする
	SetFogStartEnd(0.0f, 3000.f);
	RenderManager::GetInstance()->CreateCamera();
}

PlayScene::~PlayScene()
{
	RenderManager::GetInstance()->DeleteCamera();
}

void PlayScene::Load()
{
}

void PlayScene::ChangeState()
{
	if (!m_next) return;
	if (m_current) delete m_current;
	m_current = m_next;
	m_current->Start();
	m_next = nullptr;
}

void PlayScene::GameObjectUpdate()
{
	SceneBase::Update();
}

void PlayScene::Update()
{
	ChangeState();
	if (m_current)
		m_current->Update();

	if (m_current->GetTag() != "PlayLoad")
	{
		SceneBase::Update();
	}
	DrawFormatString(0, 0, 0xffffff, "PlayScene");
}

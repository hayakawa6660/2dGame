#include "PlayScene.h"
//#include "PlayState/PlayNewClasses/PlayNewClasses.h"
#include "PlayState/PlayLoad/PlayLoad.h"

PlayScene::PlayScene() : 
	m_next(nullptr),
	m_current(nullptr)
{
	SetNextState<PlayLoad>("PlayLoad");
}

PlayScene::~PlayScene()
{
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
}

void PlayScene::Draw()
{
	if (m_current)
		m_current->Draw();
}

#include "TitleScene.h"
//Scene
#include "Library/SceneManager/SceneManager.h"
#include "TestCollision/TestCollision.h"
#include "Library/Components/CollisionComponent/CollisionComponent.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/FadeManager/FadeManager.h"
#include "Source/System/CacheManager/CacheManager.h"
#include "Source/System/ControllerManager/ControllerManager.h"
#include "Source/System/ThreadManager/ThreadManager.h"
//Debug
#include "Source/System/DebugManager/DebugManager.h"

//#include "MyNew/MyNew.h"

TitleScene::TitleScene()
{
	CommonObjects::GetInstance()->FindGameObject<FadeManager>("FadeManager")->SetFadeLevel(0);
	TestCollision * p = SceneBase::CreateGameObject<TestCollision>("Test1");
	{
		VECTOR pos = VGet(480, 300, 0);
		p->SetPosition(pos);
		m_list.emplace_back(p);
	}
	{
		p = SceneBase::CreateGameObject<TestCollision>("Test2");
		VECTOR pos = VGet(500, 300, 0);
		p->SetPosition(pos);
		m_list.emplace_back(p);
	}
	/*
	int* t1 = new int;
	VECTOR* t2 = new VECTOR();
	*/
	/*
	//ƒXƒŒƒbƒh‚Ìì‚è•û«
	ThreadManager * p = CommonObjects::GetInstance()->FindGameObject<ThreadManager>("ThreadManager");
	p->CreateThread<void>([this] { Hoge(); });
	*/
}

TitleScene::~TitleScene()
{
	Debug::ListAllClear();
}

void TitleScene::Update()
{
	SceneBase::Update();
	for (auto it = m_list.begin(); it != m_list.end(); it++)
	{
		auto it2 = it;
		it2++;
		if (it2 == m_list.end())
			break;
		CollisionComponent * p = (*it)->GetComponent<CollisionComponent>("Col");
		CollisionComponent * p2 = (*it2)->GetComponent<CollisionComponent>("Col");
		p->SphereToSpere(p2);
	}

	ControllerManager * p = CommonObjects::GetInstance()->FindGameObject<ControllerManager>("ControllerManager");
	if (p->GetKeyOnceInput(InputComponent::KEY_ID::SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("PlayScene");
	}
#if DEBUG
	Debug::DebugPrintf(200, 0, "Title", "Title");
	//Debug::DebugPrintf(200, 20, "Title", "threadNum : %d", p->CurrentNum());
#endif
}

void TitleScene::Draw()
{
	SceneBase::Draw();
	DrawFString(10, 20, "AAA = %d", 20);
}

void TitleScene::DrawFString(int _x, int _y, const char *_format,...)
{
	va_list vlist;
	char ch[256];
	va_start(vlist, _format);
	vsprintf_s(ch, _format, vlist);
	DrawFormatString(_x, _y, 0xffffff, ch);
	va_end(vlist);
}

/*
void TitleScene::Hoge()
{
	std::lock_guard<std::mutex> lock(mtx);
	ThreadManager * p = CommonObjects::GetInstance()->FindGameObject<ThreadManager>("ThreadManager");
	int i = 0;
	while (i < 100000000)
	{
		if (SceneManager::GetInstance()->IsGameExit())
		{
			m_onThread = false;
			p->EndThread();
			return;
		}
		i++;
		m_num++;
	}
	m_onThread = false;
	p->EndThread();
}
*/
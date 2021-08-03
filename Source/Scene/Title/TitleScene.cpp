#include "TitleScene.h"
//Scene
#include "Library/SceneManager/SceneManager.h"
#include "TestCollision/TestCollision.h"
#include "Library/Components/CollisionComponent/CollisionComponent.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/FadeManager/FadeManager.h"
#include "Source/System/CacheManager/CacheManager.h"
#include "Source/System/InputManager/InputManager.h"
#include "Source/System/ThreadManager/ThreadManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
//Debug
#include "Source/System/DebugManager/DebugManager.h"
#include "Source/System/CompressManager/CompressManager.h"
//Render
#include "Library/Render/RenderManager.h"

TitleScene::TitleScene() :
	m_isNewEnd(false), m_state(STATE::NEW)
{
	CommonObjects * common = CommonObjects::GetInstance();
	common->FindGameObject<FadeManager>("FadeManager")->SetFadeLevel(0);
	m_thread = common->FindGameObject<ThreadManager>("ThreadManager");
	m_thread->CreateThread<void>([this] { Load(); });

	{	//テスト画像描画(resourceマネージャー使うの面倒だったのでその場ロード)
		ResourceManager * resource = common->FindGameObject<ResourceManager>("SceneResource");
		m_sprite.fileName = "data\\Texture\\test.png";
		m_sprite.position = VGet(300, 300, 1);
		m_sprite.sizeX = 64;
		m_sprite.sizeY = 64;
		m_sprite.handle = LoadGraph(m_sprite.fileName.c_str());
		RenderManager::GetInstance()->AddTexture("Test", m_sprite, [=]() {
			DrawRectGraph(m_sprite.position.x, m_sprite.position.y, 0, 0, m_sprite.sizeX, m_sprite.sizeY, m_sprite.handle, true, false);
		});
		//二重追加弾き確認
		RenderManager::GetInstance()->AddTexture("Test", m_sprite, [=]() {
			DrawRectGraph(m_sprite.position.x, m_sprite.position.y, 0, 0, m_sprite.sizeX, m_sprite.sizeY, m_sprite.handle, true, false);
		});
	}

	/*
	TestCollision * p = SceneBase::CreateGameObject<TestCollision>("Test1");
	{
		VECTOR pos = VGet(480, 300, 0);
		p->SetPosition(pos);
		m_list.emplace_back(p);
	}
	*/
	/*
	TestCollision * p = SceneBase::CreateGameObject<TestCollision>("Test1");
	{
		p = SceneBase::CreateGameObject<TestCollision>("Test2");
		VECTOR pos = VGet(500, 300, 0);
		p->SetPosition(pos);
		m_list.emplace_back(p);
	}
	*/
	/*
	//スレッドの作り方↓
	ThreadManager * p = CommonObjects::GetInstance()->FindGameObject<ThreadManager>("ThreadManager");
	p->CreateThread<void>([this] { Hoge(); });
	*/
}

TitleScene::~TitleScene()
{
	Debug::ListAllClear();
	//CompressManager * p = CommonObjects::GetInstance()->FindGameObject<CompressManager>("SceneCompress");
	//p->AllDeleteDirectory();
}

void TitleScene::Update()
{
	m_sprite.position.x += 0.1f;
	if (m_sprite.position.x >= 330.f)
		RenderManager::GetInstance()->RemoveTexture("Test");
	//SceneBase::Update();
	switch (m_state)
	{
	case STATE::NEW:
	{
		if (m_isNewEnd)
		{
			SceneBase::Update();
			m_state = STATE::LOAD;
		}
	}
	break;
	case STATE::LOAD:
	{
		ResourceManager *p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		if (p->IsLoadEnd())
		{
			SceneBase::Update();
			m_state = STATE::PLAY;
		}
	}
	break;
	case STATE::PLAY:
		SceneBase::Update();
		InputManager * p = CommonObjects::GetInstance()->FindGameObject<InputManager>("InputManager");
		//if (p->GetKeyOnceInput(InputComponent::KEY_ID::SPACE))
		if (p->IsTrigger("SPACE"))
			SceneManager::GetInstance()->ChangeScene("PlayScene"); // 起動が終わったらTitleを表示
		break;
	}

#if DEBUG
	Debug::DebugPrintf(200, 0, "Title", "Title");
#endif
}

void TitleScene::Load()
{
	TestCollision * p = SceneBase::CreateGameObject<TestCollision>("Test1");
	{
		VECTOR pos = VGet(480, 300, 0);
		p->SetPosition(pos);
	}
	m_thread->EndThread();
	m_isNewEnd = true;
}

/*
void TitleScene::DrawFString(int _x, int _y, const char *_format, ...)
{
	va_list vlist;
	char ch[256];
	va_start(vlist, _format);
	vsprintf_s(ch, _format, vlist);
	DrawFormatString(_x, _y, 0xffffff, ch);
	va_end(vlist);
}
*/

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


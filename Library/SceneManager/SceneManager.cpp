#include "SceneManager.h"
#include "sceneBase.h"
#include "Source/Scene/SceneFactory.h"

#include "../Common/commonObjects.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Source/System/ThreadManager/ThreadManager.h"
#include "Source/System/InputManager/InputManager.h"

//#include "Source/System/ControllerManager/ControllerManager.h"

SceneManager::SceneManager() :
	m_nextName(""), m_currentName(""), m_currentScene(nullptr), m_factory(nullptr),
	m_exit(false)
{
	m_factory = new SceneFactory();
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager* instance;
	if (instance == nullptr) {
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::Start()
{
	// 最初に動くシーンを、SceneFactoryに作ってもらう
	if (m_currentScene == nullptr)
		m_currentScene = m_factory->CreateFirst();
}

void SceneManager::Update()
{
	if (m_nextName != m_currentName) { // シーン切り替えの指定があったので
		if (m_currentScene != nullptr) { // 今までのシーンを解放
			delete m_currentScene;
			m_currentScene = nullptr;
		}
		CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource")->AllDelete();
		m_currentName = m_nextName;
		m_currentScene = m_factory->Create(m_nextName); // 次のシーンを作成
	}

	if (CommonObjects::GetInstance()->FindGameObject<InputManager>("InputManager")
		->IsTrigger("ESC"))
	{
		m_exitGame = true;
	}
	/*
	if (CommonObjects::GetInstance()->FindGameObject<ControllerManager>("ControllerManager")
		->GetKeyInput(InputComponent::KEY_ID::ESC))
	{
		m_exitGame = true;
	}
	*/
	if (m_exitGame)
	{
		ThreadManager * p = CommonObjects::GetInstance()->FindGameObject<ThreadManager>("ThreadManager");
		p->AllEnd();
		int currentThreadNum = p->CurrentNum();
		if (currentThreadNum == 0)
			m_exit = true;
	}
	else if (m_currentScene != nullptr)
		m_currentScene->Update();
}

void SceneManager::Release()
{
	if (m_currentScene != nullptr) {
		delete m_currentScene;
		m_currentScene = nullptr;
	}
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	m_nextName = sceneName;
}

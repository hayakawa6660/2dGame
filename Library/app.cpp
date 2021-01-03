#include "App.h"
#include "SceneManager/SceneManager.h"
#include "Common/commonObjects.h"

void AppInit()
{
	SceneManager::GetInstance()->Start();
	CommonObjects::GetInstance()->Start();
}

void AppUpdate()
{
	SceneManager::GetInstance()->Update();
	CommonObjects::GetInstance()->Update();
}

void AppDraw()
{
	SceneManager::GetInstance()->Draw();
	CommonObjects::GetInstance()->Draw();
}

void AppRelease()
{
	SceneManager::GetInstance()->Release();
	CommonObjects::GetInstance()->Release();
}

bool IsExitGame()
{
	return SceneManager::GetInstance()->IsExit();
}

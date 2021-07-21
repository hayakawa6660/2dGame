#include "App.h"
#include "SceneManager/SceneManager.h"
#include "Common/commonObjects.h"
#include "Render/RenderManager.h"

void AppInit()
{
	SceneManager::GetInstance()->Start();
	CommonObjects::GetInstance()->Start();
	RenderManager::GetInstance();
}

void AppUpdate()
{
	SceneManager::GetInstance()->Update();
	CommonObjects::GetInstance()->Update();
	RenderManager::GetInstance()->Update();
}

void AppDraw()
{
	RenderManager::GetInstance()->Draw();
}

void AppRelease()
{
	SceneManager::GetInstance()->Release();
	CommonObjects::GetInstance()->Release();
	RenderManager::GetInstance()->Release();
}

bool IsExitGame()
{
	return SceneManager::GetInstance()->IsExit();
}

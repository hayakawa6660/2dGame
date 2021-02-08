#include "RenderManager.h"

#include "Library/Common/commonObjects.h"
#include "Shader/Shader.h"

RenderManager::RenderManager(SceneBase * _scene) :
	GameObject(nullptr)
{
	m_shader = CommonObjects::GetInstance()->CreateGameObject<Shader>("Shader");
}

RenderManager::~RenderManager()
{
}

void RenderManager::Start()
{
}

void RenderManager::Update()
{
}

void RenderManager::ShadowSetUp()
{
}
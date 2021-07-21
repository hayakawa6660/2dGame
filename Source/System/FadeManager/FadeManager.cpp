#include "FadeManager.h"
#include <DxLib.h>
#include <assert.h>

#include "Library/Common/commonObjects.h"
#include "../ResourceManager/ResourceManager.h"

FadeManager::FadeManager(SceneBase * _scene) :
	GameObject(nullptr),
	m_fadeLevel(255)
{
	m_texture.fileName = "data\\Texture\\Fade.png";
	m_texture.handle = -1;
	m_texture.sizeX = 1366;
	m_texture.sizeY = 768;

	ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	rsc->TextureLoad(m_texture.fileName);
}

FadeManager::~FadeManager()
{
}

void FadeManager::Update()
{
	if (m_texture.handle < 0)
	{
		ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
		m_texture.handle = rsc->GetHandle(m_texture.fileName);
	}
}
/*
void FadeManager::Draw()
{
	//フェードを見やすくするため一旦白に
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_fadeLevel);
	DrawExtendGraph(0, 0, m_texture.sizeX, m_texture.sizeY, m_texture.handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
*/
void FadeManager::FadeStart(int _fadeCount)
{
	m_fadeCount = (float)_fadeCount;
	m_fadeEnd = false;
}

void FadeManager::FadeIn()
{
	m_fadeLevel -= (m_fadeLevel / m_fadeCount);
	m_fadeCount--;
	if (m_fadeLevel <= 0.f) {
		m_fadeLevel = 0.f;
		m_fadeEnd = true;
	}
}

void FadeManager::FadeOut()
{
	m_fadeLevel += ((255 - m_fadeLevel) / m_fadeCount);
	m_fadeCount--;
	if (m_fadeLevel >= 255.f) {
		m_fadeLevel = 255.f;
		m_fadeEnd = true;
	}
}

void FadeManager::SetFadeLevel(float _fadeLevel)
{
	m_fadeLevel = _fadeLevel;
}

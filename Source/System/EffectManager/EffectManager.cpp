#include "EffectManager.h"
#include "EffectBase.h"

#include "FireFlowar/FireFlowar.h"

#include "../ResourceManager/ResourceManager.h"
#include "../../../Library/Common/commonObjects.h"

#include "../../../Library/Common/commonObjects.h"
#include "../../System/ResourceManager/ResourceManager.h"

#include <string>

EffectManager::EffectManager(SceneBase * _scene) :
	GameObject(nullptr),
	m_isLoadEnd(false)
{
	m_effectList.clear();
	/*
	m_texture[(int)TYPE::FIRE_FLOWER].fileName = "data\\texture\\effect\\particle_000.png";
	m_texture[(int)TYPE::FIRE_FLOWER].handle = -1;
	ResourceManager * p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	for (auto &it : m_texture)
	{
		p->TextureLoad(it.fileName);
	}
	*/
}

EffectManager::~EffectManager()
{
	m_effectList.clear();
}

void EffectManager::Update()
{
	/*
	if (!m_isLoadEnd)
	{
		LoadUpdate();
	}
	*/
	for (auto it = m_effectList.begin(); it != m_effectList.end();)
	{
		if ((*it)->CanDestroy())
		{
			(*it)->DestroyMe();
			it = m_effectList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void EffectManager::Create(TYPE _type, const VECTOR & _pos, const VECTOR & _rot, const VECTOR _scl, const MATRIX _mat)
{
	EffectBase* p = nullptr;
	switch (_type)
	{
	case TYPE::FIRE_FLOWER:	p = CommonObjects::GetInstance()->CreateGameObject<FireFlowarEffect>("FireFlowar");		break;
	default:	break;
	}
	if (p != nullptr)
	{
		CommonObjects::GetInstance()->SetDrawOrder(p, 1000);
		m_effectList.emplace_back(p);

		p->SetInfo(m_texture[(int)_type], _pos, _rot, _scl, _mat);
	}
}

void EffectManager::LoadUpdate()
{
	ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	for (auto &it : m_texture)
	{
		if (it.handle < 0)
		{
			if (!rsc->CheckHandle(it.fileName))	//このファイルのロードが終わっているか確認
				return;
			//終わっていたらハンドルを入れる
			it.handle = rsc->GetHandle(it.fileName);
		}
	}
	m_isLoadEnd = true;
}

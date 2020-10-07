#include "LoadManager.h"
#include "LoadData/LoadData.h"
#include "LoadDraw/LoadDraw.h"

#include "../../../Library/Common/commonObjects.h"
#include "../ResourceManager/ResourceManager.h"

LoadManager::LoadManager(SceneBase * _scene) :
	GameObject(nullptr)
{
	/*
	m_imageList.clear();
	Sprite_Info info;
	info.fileName = "data\\texture\\Load\\Load.png";
	info.handle = -1;
	info.sizeX = 1366;
	info.sizeY = 768;
	m_imageList.emplace(SPRITE_TYPE::BACK_GROUND, info);
	info.fileName = "data\\texture\\load\\road_anim.png";
	info.handle = -1;
	info.sizeX = 400;
	info.sizeY = 280;
	m_imageList.emplace(SPRITE_TYPE::LOAD_CHARA, info);

	ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	for (auto &it : m_imageList)
	{
		rsc->TextureLoad(it.second.fileName);
	}
	*/
}

LoadManager::~LoadManager()
{
	//m_imageList.clear();
}

void LoadManager::Start()
{
}

void LoadManager::Update()
{
	/*
	if (!m_isLoadEnd)
		if (!LoadCheck())
			return;
			*/
}

void LoadManager::Draw()
{
}

bool LoadManager::LoadCheck()
{
	if (!m_isLoadEnd)
	{
		ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
		for (auto &it : m_imageList)
		{
			if (it.second.handle < 0)
			{
				if (!rsc->CheckHandle(it.second.fileName))	//このファイルのロードが終わっているか確認
					return false;
				//終わっていたらハンドルを入れる
				it.second.handle = rsc->GetHandle(it.second.fileName);
			}
		}
		//ロードが全て終わっているのが確認できたら次からチェックしない
		m_isLoadEnd = true;
	}
	return true;
}

void LoadManager::SetActive(bool _flag)
{
	if (_flag)
	{
		LoadData * data = CommonObjects::GetInstance()->CreateGameObject<LoadData>("LoadData");
		data->SetParent(this);
		CommonObjects::GetInstance()->SetDrawOrder(data, 600);

		LoadDraw * draw = CommonObjects::GetInstance()->CreateGameObject<LoadDraw>("LoadDraw");
		draw->SetParent(this);
		draw->SetSprite(SPRITE_TYPE::BACK_GROUND, m_imageList[SPRITE_TYPE::BACK_GROUND], VGet(0, 0, 0));
		draw->SetSprite(SPRITE_TYPE::LOAD_CHARA, m_imageList[SPRITE_TYPE::LOAD_CHARA], VGet(1000, 500, 0));
		CommonObjects::GetInstance()->SetDrawOrder(draw, 500);
	}
	else
	{
		CommonObjects::GetInstance()->FindGameObject<LoadData>("LoadData")->DestroyMe();
		CommonObjects::GetInstance()->FindGameObject<LoadDraw>("LoadDraw")->DestroyMe();
	}
}

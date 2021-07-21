#include "LoadDraw.h"

LoadDraw::LoadDraw(SceneBase * _scene) :
	GameObject(nullptr),
	m_animCount(0)
{
	m_infoList.clear();
}

LoadDraw::~LoadDraw()
{
	m_infoList.clear();
}

void LoadDraw::Start()
{
}

void LoadDraw::Update()
{
	m_animCount++;
}

/*
void LoadDraw::Draw()
{
	for (auto & it : m_infoList)
	{
		switch (it.first)
		{
		case LoadManager::SPRITE_TYPE::BACK_GROUND:
			DrawRectGraph((int)it.second.pos.x, (int)it.second.pos.y, 0, 0, it.second.sprite.sizeX, it.second.sprite.sizeY, it.second.sprite.handle, true, false);
			break;
		case LoadManager::SPRITE_TYPE::LOAD_CHARA:
			int cellX = m_animCount / 4 % 4;
			DrawRectGraph((int)it.second.pos.x, (int)it.second.pos.y, cellX * it.second.sprite.sizeX, 0, it.second.sprite.sizeX, it.second.sprite.sizeY, it.second.sprite.handle, true, false);
			break;
		}
	}
}
*/

void LoadDraw::SetActive(bool _flag)
{
	m_active = _flag;
}

void LoadDraw::SetSprite(LoadManager::SPRITE_TYPE _type, Sprite_Info & _info, VECTOR _pos)
{
	LoadDraw_Info info;
	info.sprite.handle = _info.handle;
	info.sprite.sizeX = _info.sizeX;
	info.sprite.sizeY = _info.sizeY;
	info.pos = _pos;
	m_infoList.emplace(_type, info);
}
#pragma once

#include "Library/GameObject/GameObject.h"
#include "../LoadManager.h"
#include "Source/Common.h"

#include <unordered_map>

class LoadDraw : public GameObject
{
public:
	LoadDraw(SceneBase * _scene);
	~LoadDraw();
private:
	void Start()override;
	void Update()override;
	void Draw()override;
public:
	void SetActive(bool _flag);
	void SetSprite(LoadManager::SPRITE_TYPE _type, Sprite_Info & _info, VECTOR _pos);
private:
	bool m_active;
	struct LoadDraw_Info
	{
		Sprite_Info sprite;
		VECTOR pos;
	};
	int m_animCount;
	std::unordered_map<LoadManager::SPRITE_TYPE, LoadDraw_Info> m_infoList;
};
#pragma once

#include "../../../Library/GameObject/GameObject.h"
#include "../../Common.h"
#include <array>

class EffectBase;
class EffectManager : public GameObject
{
public:
	enum class TYPE
	{
		FIRE_FLOWER = 0,
		MAX,
	};
	EffectManager(SceneBase * _scene);
	~EffectManager();
private:
	void Update()override;
public:
	void Create(TYPE _type, const VECTOR &_pos, const VECTOR &_rot = VGet(0, 0, 0), const VECTOR _scl = VGet(1, 1, 1), const MATRIX _mat = MGetIdent());
private:
	void LoadUpdate();
private:
	std::array<Sprite_Info, (int)TYPE::MAX> m_texture;
	std::list<EffectBase*> m_effectList;
	bool m_isLoadEnd;
};
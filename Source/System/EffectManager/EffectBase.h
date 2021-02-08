#pragma once

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

class EffectBase : public GameObject
{
public:
	enum class DISPLAY_TYPE
	{
		DISPLAY = 0,	//画面エフェクト
		WORLD,			//3D空間
	};
public:
	EffectBase(SceneBase * _scene) : GameObject(_scene) {}
	virtual ~EffectBase() {}
	virtual void Start()override {}
	virtual void Update()override {}
	virtual void Draw()override {}

	void SetInfo(Sprite_Info _info, VECTOR _pos, VECTOR _rot, VECTOR _scl, MATRIX _mat)
	{
		m_info = _info;
		GameObject::SetPosition(_pos);
		GameObject::SetRotation(_rot);
		GameObject::SetScale(_scl);
		GameObject::SetMatrix(_mat);
	}
private:
	Sprite_Info m_info;
	bool m_canDestroy;
public:
	const Sprite_Info &GetTexture() { return m_info; }
	bool CanDestroy()const { return m_canDestroy; }
	void Destroyed() { m_canDestroy = true; }
};
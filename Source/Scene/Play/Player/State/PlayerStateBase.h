#pragma once
#include "Library/GameObject/GameObject.h"
#include "../PlayerMovement.h"
#include "../Player.h"

class PlayerStateBase :public GameObject
{
public:
	PlayerStateBase(SceneBase* _scene, PlayerMovement* _movement) : GameObject(_scene), m_movement(_movement) {}
	virtual ~PlayerStateBase() {}
	virtual void Update() override {}
protected:
	virtual void CheckInput() {};
	Player* GetPlayer() const { return dynamic_cast<Player*>(GameObject::GetParent()); }

	PlayerMovement* m_movement;
};
#pragma once
#include "Library/GameObject/GameObject.h"
#include "PlayerStateBase.h"

class PlayerMoveState : public PlayerStateBase 
{
public:
	PlayerMoveState(Player* _player, PlayerMovement* _movement);
	~PlayerMoveState();
private:
	void Update()override;
};
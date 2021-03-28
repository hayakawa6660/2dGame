#pragma once
#include "Library/GameObject/GameObject.h"
#include "PlayerStateBase.h"

class PlayerWaitState : public PlayerStateBase
{
public:
	PlayerWaitState(Player* _player, PlayerMovement* _movement);
	~PlayerWaitState();
private:
	void Update()override;
};
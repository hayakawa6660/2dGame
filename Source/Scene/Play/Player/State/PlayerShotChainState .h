#pragma once
#include "Library/GameObject/GameObject.h"
#include "PlayerStateBase.h"

class PlayerShotChainState : public PlayerStateBase
{
public:
	PlayerShotChainState(Player* _player, PlayerMovement* _movement);
	~PlayerShotChainState();
}; 
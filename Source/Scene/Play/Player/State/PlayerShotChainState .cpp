#include "PlayerShotChainState .h"
#include "PlayerMovement.h"

PlayerShotChainState::PlayerShotChainState(Player* _player, PlayerMovement* _movement) :
	PlayerStateBase(_player, _movement)
{
}

PlayerShotChainState::~PlayerShotChainState()
{
}

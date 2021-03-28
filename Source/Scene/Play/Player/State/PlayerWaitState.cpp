#include "PlayerWaitState.h"
#include "PlayerMovement.h"

PlayerWaitState::PlayerWaitState(Player* _player, PlayerMovement* _movement) :
	PlayerStateBase(_player, _movement)
{ 
}

PlayerWaitState::~PlayerWaitState()
{
}

void PlayerWaitState::Update()
{
}

#include "PlayerMoveState.h"
#include "PlayerMovement.h"

PlayerMoveState::PlayerMoveState(Player* _player, PlayerMovement* _movement):
	PlayerStateBase(_player, _movement)
{
}

PlayerMoveState::~PlayerMoveState()
{
}

void PlayerMoveState::Update()
{
}

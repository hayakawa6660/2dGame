#include "PlayerJumpState.h"
#include "../Wait/WaitState.h"
#include "../Move/PlayerMoveState.h"

PlayerJumpState::PlayerJumpState(SceneBase* _scene, PlayerMovement* _movement) :
	PlayerStateBase(_scene, _movement)
{
	m_movement->Jump(10.0f);
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Update()
{
	CheckInput();
}

void PlayerJumpState::CheckInput()
{
	auto player = GetPlayer();
	if (!player)return;
	if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_RIGHT)) {
		player->SetNextState<PlayerMoveState>();
	}
	player->SetNextState<WaitState>();
}

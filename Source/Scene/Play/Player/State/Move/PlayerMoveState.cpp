#include "PlayerMoveState.h"
#include "../../PlayerMovement.h"
#include "../Wait/WaitState.h"
#include "../Jump/PlayerJumpState.h"

PlayerMoveState::PlayerMoveState(SceneBase* _scene, PlayerMovement* _movement) :
	PlayerStateBase(_scene, _movement)
{
	m_movement->SetMoveSpeed(0.2f,1.5f,0.8f);
}

PlayerMoveState::~PlayerMoveState()
{
}

void PlayerMoveState::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		m_movement->MoveLeft();
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		m_movement->MoveRight();
	}
	CheckInput();
}

void PlayerMoveState::CheckInput()
{
	auto player = GetPlayer();
	if (!player)return;
	if (!CheckHitKey(KEY_INPUT_LEFT) && !CheckHitKey(KEY_INPUT_RIGHT)) {
		player->SetNextState<WaitState>();
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		player->SetNextState<PlayerJumpState>();
	}
}

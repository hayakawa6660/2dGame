#include "WaitState.h"
#include "../Move/PlayerMoveState.h"
#include "../Jump/PlayerJumpState.h"
WaitState::WaitState(SceneBase* _scene, PlayerMovement* _movement) :
	PlayerStateBase(_scene, _movement)
{
}

WaitState::~WaitState()
{
}

void WaitState::Update()
{
	CheckInput();
}

void WaitState::CheckInput()
{
	auto player = GetPlayer();
	if (!player)return;
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT)) {
		player->SetNextState<PlayerMoveState>();
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		player->SetNextState<PlayerJumpState>();
	}
}

#pragma once
#include "../PlayerStateBase.h"

class PlayerJumpState : public PlayerStateBase{
public:
	PlayerJumpState(SceneBase* _scene, PlayerMovement* _movement);
	~PlayerJumpState();
	void Update()override;
	void CheckInput()override;
};
#pragma once
#include "../PlayerStateBase.h"
class PlayerMoveState :public PlayerStateBase{
public:
	PlayerMoveState(SceneBase* _scene, PlayerMovement* _movement);
	~PlayerMoveState();


private:
	void Update()override;
	void CheckInput()override;
};
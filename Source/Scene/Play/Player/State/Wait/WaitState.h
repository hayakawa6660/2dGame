#pragma once
#include "../PlayerStateBase.h"
class WaitState : public PlayerStateBase {
public:
	WaitState(SceneBase* _scene,PlayerMovement* _movement);
	~WaitState();
private:
	void Update()override;
	void CheckInput()override;

};
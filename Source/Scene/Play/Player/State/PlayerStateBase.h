#pragma once
#include "../Player.h"

class PlayerStateBase : public GameObject{
public:
	PlayerStateBase(Player* _player);
	~PlayerStateBase();
private:
	virtual void Update()override;
};
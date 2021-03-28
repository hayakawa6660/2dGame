#pragma once
class Player;
class PlayerMovement;
class PlayerStateBase : public GameObject{
public:
	PlayerStateBase(Player* _player, PlayerMovement* _movement) : m_player(_player), m_movement(_movement){};
	~PlayerStateBase() {};

	virtual void Update()override {}
protected:
	Player* m_player;
	PlayerMovement* m_movement;
};
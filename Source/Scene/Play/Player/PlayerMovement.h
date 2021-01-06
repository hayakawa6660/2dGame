#pragma once
#include "Library/GameObject/GameObject.h"

class PlayerMovement : public GameObject {
public:
	PlayerMovement();
	~PlayerMovement();
	void Update()override;

	void SetMoveSpeed(float _speed, float _maxSpeed, float _decelerationRate);
	void Jump(float _power);
	void MoveLeft();
	void MoveRight();
	void SetVelosity(const VECTOR& _velosity) { m_velocity = _velosity; }
	void SetGravity(float _gravity) { m_gravity = _gravity; }
	bool GetGroundedFlag() { return m_grounded; }
private:
	VECTOR m_velocity;
	float m_gravity;
	float m_moveSpeed;
	float m_maxSpeed;
	float m_decelerationRate;
	bool m_moveFlag;
	bool m_grounded;
};
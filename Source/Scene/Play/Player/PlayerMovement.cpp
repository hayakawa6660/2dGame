#include "PlayerMovement.h"
#include "Player.h"

PlayerMovement::PlayerMovement():
	m_velocity(VGet(0.f,0.f,0.f)),
	m_gravity(0.4f),
	m_moveSpeed(1.0f),
	m_grounded(false)
{
	SetMoveSpeed(0.1f, 0.5f, 0.7f);
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::Update()
{
	VECTOR position = GameObject::GetPosition();
	position += m_velocity;
	if (position.y < 500) {//仮判定
		m_velocity.y = m_velocity.y + m_gravity;
	}
	else {
		m_velocity.y = 0.f;
		position.y = 500.f;
		m_grounded = true;
	}
	//移動減衰
	if (!m_moveFlag) {
		m_velocity.x = m_velocity.x * m_decelerationRate;
	}
	m_moveFlag = false;

	//movementクラスにポジションをセット
	GameObject::SetPosition(position);
	//プレイヤークラスにmovementクラスのポジションをセット
	GameObject::GetParent()->SetPosition(GameObject::GetPosition());
}

void PlayerMovement::SetMoveSpeed(float _speed,float _maxSpeed, float _decelerationRate)
{
	m_moveSpeed = _speed;
	m_maxSpeed = _maxSpeed;
	m_decelerationRate = _decelerationRate;
}

void PlayerMovement::Jump(float _power)
{
	if (_power < 0.0f) { return; }
	if (m_grounded) 
	{
		m_velocity.y -= _power;
		m_grounded = false;
	}
}

void PlayerMovement::MoveLeft()
{
	m_velocity.x = abs(m_velocity.x) < m_maxSpeed ? m_velocity.x - m_moveSpeed : -m_maxSpeed;
	m_moveFlag = true;
}

void PlayerMovement::MoveRight()
{
	m_velocity.x = abs(m_velocity.x) < m_maxSpeed ? m_velocity.x + m_moveSpeed : m_maxSpeed;
	m_moveFlag = true;
}

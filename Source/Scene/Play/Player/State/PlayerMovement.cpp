#include "PlayerMovement.h"

#include "Library/Common/commonObjects.h"

#include <assert.h>
PlayerMovement::PlayerMovement() :
	//m_input(nullptr), 
	m_movementAxis(0.f),
	m_movementSpeed(0.0001f),
	m_movementMaxSpeed(1.f),
	m_rotateSpeed(0.1f),
	velocity(VGet(0,0,0))
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::MovementUpdate(MATRIX* _matrix)
{
	MoveToKeyAngleUpdate();
	VelocityUpdate();
	MATRIX mat = MGetRotY(m_movementAxis) * MGetTranslate(velocity);
	*_matrix = MMult(*_matrix, mat);
}

void PlayerMovement::SetMovemetSpeed(float _movementSpeed)
{
	m_movementSpeed = _movementSpeed;
}

void PlayerMovement::VelocityUpdate()
{
	/*
	if (!m_input)
		return;
	VECTOR dir = VGet(0, 0, 0);
	if (m_input->GetKeyInput(InputComponent::KEY_ID::W)) {
		dir.z = -1.f;
	}
	else if (m_input->GetKeyInput(InputComponent::KEY_ID::S)) {
		dir.z = 1.f;
	}

	if (m_input->GetKeyInput(InputComponent::KEY_ID::A)) {
		dir.x = 1.f;
	}
	else if (m_input->GetKeyInput(InputComponent::KEY_ID::D)) {
		dir.x = -1.f;
	}
	velocity += dir * m_movementSpeed;
	velocity = VSize(velocity) < m_movementMaxSpeed ? velocity : dir * m_movementMaxSpeed;
	*/
}

void PlayerMovement::MoveToKeyAngleUpdate()
{
	/*
	if (!m_input)
		return;
	float axis = 0;
	if (m_input->GetKeyInput(InputComponent::KEY_ID::LEFT)) {
		axis += m_rotateSpeed;
	}
	else if (m_input->GetKeyInput(InputComponent::KEY_ID::RIGHT)) {
		axis -= m_rotateSpeed;
	}
	m_movementAxis += axis;
	*/
}


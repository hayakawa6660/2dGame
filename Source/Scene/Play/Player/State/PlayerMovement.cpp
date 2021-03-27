#include "PlayerMovement.h"

#include "Library/Common/commonObjects.h"
#include "Library/Components/InputComponent/InputComponent.h"
#include <assert.h>
PlayerMovement::PlayerMovement() :m_input(nullptr), m_moveAxis(0.f),m_rotateSpeed(0.1f)
{
	m_input = CommonObjects::GetInstance()->FindGameObject<InputComponent>("ControllerManager");
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::UpdateMove(MATRIX* matrix)
{
	MATRIX m = *matrix;
	m = MGetRotY(GetMoveToKeyAngle()) * m;
	*matrix = m;
}

float PlayerMovement::GetMoveToKeyAngle()
{
	if (m_input->GetKeyInputType(InputComponent::KEY_ID::LEFT)) {
		m_moveAxis += m_rotateSpeed;
	}
	else if (m_input->GetKeyInputType(InputComponent::KEY_ID::RIGHT)) {
		m_moveAxis -= m_rotateSpeed;
	}
	return m_moveAxis;
}


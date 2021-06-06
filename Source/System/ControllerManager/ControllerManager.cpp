/*
#include "ControllerManager.h"

#include <math.h>

ControllerManager::ControllerManager(SceneBase * _scene) :
	GameObject(_scene),
	m_lastInput(TRUE),
	m_debugKey(FALSE)
{
	m_input = AddComponent<InputComponent>("InputComponent");
}

ControllerManager::~ControllerManager()
{
}

void ControllerManager::Update()
{
	GameObject::Update();
}

bool ControllerManager::DebugKeyInput()
{
	m_lastInput = m_debugKey;
	m_debugKey = 0;

	if (m_input->GetKeyInputType(InputComponent::KEY_ID::ALT) &&
		m_input->GetKeyInputType(InputComponent::KEY_ID::CTRL))
		m_debugKey = true;
	else if (m_input->GetXInputType(InputComponent::XCTR_ID::RB) &&
		m_input->GetXInputType(InputComponent::XCTR_ID::LB) &&
		m_input->GetXInputType(InputComponent::XCTR_ID::START) &&
		m_input->GetXInputType(InputComponent::XCTR_ID::SELECT))
		m_debugKey = true;

	return (~m_lastInput & m_debugKey);
}

bool ControllerManager::GetKeyOnceInput(InputComponent::KEY_ID _type)
{
	return m_input->GetKeyOnceInputType(_type);
}

bool ControllerManager::GetKeyInput(InputComponent::KEY_ID _type)
{
	return m_input->GetKeyInputType(_type);
}

bool ControllerManager::GetXOnceInput(InputComponent::XCTR_ID _type)
{
	return m_input->GetXOnceInputType(_type);
}

bool ControllerManager::GetXInputType(InputComponent::XCTR_ID _type)
{
	return m_input->GetXInputType(_type);
}

//右スティック
bool ControllerManager::CheckStickSafetyRX() const
{
	if (abs(m_input->GetStickRX()) > RIGHT_STICK_SAFETY) {
		return true;
	}
	return false;
}

bool ControllerManager::CheckStickSafetyRY() const
{
	if (abs(m_input->GetStickRY()) > RIGHT_STICK_SAFETY) {
		return true;
	}
	return false;
}

bool ControllerManager::CheckStickSafetyLX() const
{
	if (abs(m_input->GetStickLX()) > LEFT_STICK_SAFETY) {
		return true;
	}
	return false;
}

bool ControllerManager::CheckStickSafetyLY() const
{
	if (abs(m_input->GetStickLY()) > LEFT_STICK_SAFETY) {
		return true;
	}
	return false;
}

float ControllerManager::GetRightStickAngle() const
{
	if (CheckStickSafetyRY() || CheckStickSafetyRX()) {
		float angle = atan2f((float)m_input->GetStickRY(), (float)m_input->GetStickRX());
		return angle;
	}
	return 0.0f;
}

VECTOR ControllerManager::GetLStick_XY()
{
	VECTOR pos = VGet((float)m_input->GetStickLX(), (float)m_input->GetStickLY(), 0.f);
	pos.x = (float)((int)pos.x / (1 << 7));
	pos.y = (float)((int)pos.y / (1 << 7));
	if (VSize(pos) < 40.f) {
		pos = VGet(0, 0, 0);
	}
	return pos;
}

VECTOR ControllerManager::GetRStick_XY()
{
	VECTOR pos = VGet((float)m_input->GetStickRX(), (float)m_input->GetStickRY(), 0.f);
	pos.x = (float)((int)pos.x / (1 << 7));
	pos.y = (float)((int)pos.y / (1 << 7));
	if (VSize(pos) < 40.f) {
		pos = VGet(0, 0, 0);
	}
	return pos;
}

float ControllerManager::GetLeftStickAngle() const
{
	if (CheckStickSafetyLX() || CheckStickSafetyLY()) {
		float angle = atan2f((float)m_input->GetStickLY(), (float)m_input->GetStickLX());
		return angle;
	}
	return 0.0f;
}
*/
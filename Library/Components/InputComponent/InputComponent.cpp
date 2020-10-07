#include "InputComponent.h"
#include <DxLib.h>

InputComponent::InputComponent() :
	m_xLastInput(true),
	m_xInput(0),
	m_controllerNum(1),
	m_keyInput(0),
	m_keyLastInput(true)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update()
{
	XCtrUpdate();
	KeyUpdate();
}

void InputComponent::XCtrUpdate()
{
	GetJoypadXInputState(m_controllerNum, &m_xState);
	XINPUT_STATE *p = &m_xState;

	m_xLastInput = m_xInput;
	m_xInput = 0;

	if (p->Buttons[12] != 0)
		m_xInput |= (int)XCTR_ID::A;
	if (p->Buttons[13] != 0)
		m_xInput |= (int)XCTR_ID::B;
	if (p->Buttons[14] != 0)
		m_xInput |= (int)XCTR_ID::X;
	if (p->Buttons[15] != 0)
		m_xInput |= (int)XCTR_ID::Y;

	if (p->Buttons[0] != 0)
		m_xInput |= (int)XCTR_ID::UP;
	if (p->Buttons[1] != 0)
		m_xInput |= (int)XCTR_ID::DOWN;
	if (p->Buttons[2] != 0)
		m_xInput |= (int)XCTR_ID::LEFT;
	if (p->Buttons[3] != 0)
		m_xInput |= (int)XCTR_ID::RIGHT;

	if (p->Buttons[4] != 0)
		m_xInput |= (int)XCTR_ID::START;
	if (p->Buttons[5] != 0)
		m_xInput |= (int)XCTR_ID::SELECT;

	//�X�e�B�b�N������
	if (p->Buttons[6] != 0)
		m_xInput |= (int)XCTR_ID::LSTICK;
	if (p->Buttons[7] != 0)
		m_xInput |= (int)XCTR_ID::RSTICK;

	if (p->Buttons[8] != 0)
		m_xInput |= (int)XCTR_ID::LB;
	if (p->Buttons[9] != 0)
		m_xInput |= (int)XCTR_ID::RB;
}

void InputComponent::KeyUpdate()
{
	m_keyLastInput = m_keyInput;
	m_keyInput = 0;

	if (CheckHitKey(KEY_INPUT_UP) != 0)
		m_keyInput |= (int)KEY_ID::UP;
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)
		m_keyInput |= (int)KEY_ID::DOWN;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0)
		m_keyInput |= (int)KEY_ID::LEFT;
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
		m_keyInput |= (int)KEY_ID::RIGHT;

	if (CheckHitKey(KEY_INPUT_W) != 0)
		m_keyInput |= (int)KEY_ID::W;
	if (CheckHitKey(KEY_INPUT_A) != 0)
		m_keyInput |= (int)KEY_ID::A;
	if (CheckHitKey(KEY_INPUT_S) != 0)
		m_keyInput |= (int)KEY_ID::S;
	if (CheckHitKey(KEY_INPUT_D) != 0)
		m_keyInput |= (int)KEY_ID::D;

	if (CheckHitKey(KEY_INPUT_RALT) != 0 || CheckHitKey(KEY_INPUT_LALT) != 0)
		m_keyInput |= (int)KEY_ID::ALT;
	if (CheckHitKey(KEY_INPUT_RCONTROL) != 0 || CheckHitKey(KEY_INPUT_LCONTROL) != 0)
		m_keyInput |= (int)KEY_ID::CTRL;
	if (CheckHitKey(KEY_INPUT_LSHIFT) != 0 || CheckHitKey(KEY_INPUT_RSHIFT) != 0)
		m_keyInput |= (int)KEY_ID::SHIFT;
	if (CheckHitKey(KEY_INPUT_SPACE) != 0)
		m_keyInput |= (int)KEY_ID::SPACE;
}

bool InputComponent::GetXOnceInputType(XCTR_ID _type)
{
	return (((~m_xLastInput & m_xInput) & (int)_type) != 0);
}

bool InputComponent::GetXInputType(XCTR_ID _type)
{
	return ((m_xInput & (int)_type) != 0);
}

int InputComponent::GetStickRX()
{
	return m_xState.ThumbRX;
}

int InputComponent::GetStickRY()
{
	return m_xState.ThumbRY;
}

int InputComponent::GetStickLX()
{
	return m_xState.ThumbLX;
}

int InputComponent::GetStickLY()
{
	return m_xState.ThumbLY;
}

bool InputComponent::GetKeyOnceInputType(KEY_ID _type)
{
	return (((~m_keyLastInput & m_keyInput) & (int)_type) != 0);
}

bool InputComponent::GetKeyInputType(KEY_ID _type)
{
	return ((m_keyInput & (int)_type) != 0);
}

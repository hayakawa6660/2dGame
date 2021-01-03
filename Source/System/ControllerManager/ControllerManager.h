#pragma once

#include "Library/GameObject/GameObject.h"

#include "Library/Components/InputComponent/InputComponent.h"

class ControllerManager : public GameObject
{
public:
	ControllerManager(SceneBase * _scene);
	~ControllerManager();

private:
	void Start()override {}
	void Update()override;
	void Draw()override {}

	/// <summary>
	/// �X�e�B�b�N�̃Z�[�t�e�B
	/// </summary>
	/// <returns>�S�Ċ������Ă�����TRUE</returns>
	bool CheckStickSafetyLX() const;
	bool CheckStickSafetyLY() const;
	bool CheckStickSafetyRX() const;
	bool CheckStickSafetyRY() const;
public:
	//�X�e�B�b�N�̌����𓾂�
	float GetLeftStickAngle() const;
	float GetRightStickAngle() const;

	VECTOR GetLStick_XY();
	VECTOR GetRStick_XY();

private:
	InputComponent * m_input;

	static const int LEFT_STICK_SAFETY = 15000;
	static const int RIGHT_STICK_SAFETY = 10000;

	int m_lastInput;
	int m_debugKey;
public:
	bool DebugKeyInput();
	bool GetKeyOnceInput(InputComponent::KEY_ID _type);
	bool GetKeyInput(InputComponent::KEY_ID _type);

	bool GetXOnceInput(InputComponent::XCTR_ID _type);
	bool GetXInputType(InputComponent::XCTR_ID _type);
};
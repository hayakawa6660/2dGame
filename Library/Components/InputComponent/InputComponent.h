#pragma once

#include "../ComponentBase.h"
class InputComponent : public ComponentBase
{
public:
	//XBOX�R���g���[���[��ID
	enum class XCTR_ID : int
	{
		A		=	1 << 0,
		B		=	1 << 1,
		X		=	1 << 2,
		Y		=	1 << 3,
		UP		=	1 << 4,
		DOWN	=	1 << 5,
		RIGHT	=	1 << 6,
		LEFT	=	1 << 7,
		LB		=	1 << 8,
		RB		=	1 << 9,
		START	=	1 << 10,
		SELECT	=	1 << 11,
		RSTICK	=	1 << 12,
		LSTICK	=	1 << 13,
	};

	//�L�[�{�[�h��ID
	enum class KEY_ID : int
	{
		UP		= 1 << 0,
		DOWN	= 1 << 1,
		RIGHT	= 1 << 2,
		LEFT	= 1 << 3,
		W		= 1 << 4,
		A		= 1 << 5,
		S		= 1 << 6,
		D		= 1 << 7,
		ALT		= 1 << 8,
		CTRL	= 1 << 9,
		SHIFT	= 1 << 10,
		SPACE	= 1 << 11,
		ESC		= 1 << 12,
	};

public:
	InputComponent();
	~InputComponent();
private:
	void Update()override;

	void XCtrUpdate();

	void KeyUpdate();
private:
	//XBOX�R���g���[���[
	int m_xInput;
	int m_xLastInput;
	XINPUT_STATE m_xState;
	int m_controllerNum;
	//�L�[�{�[�h
	int m_keyInput;
	int m_keyLastInput;
public:
	/// <summary>
	/// ���ڂ̃R���g���[���[�����Z�b�g����
	/// ��Ƀv���C���[����������ꍇ�Ŏg��
	/// </summary>
	void SetControllerNum(int _num) { m_controllerNum = _num; }

	/// <summary>
	/// XBOX�R���g���[���[�̓��͂���n�߂��擾����
	/// ��t���[���ȍ~�̓��͎͂󂯕t���Ȃ�
	/// </summary>
	/// <param name="_type">INPUT_TYPE�̃^�C�v</param>
	bool GetXOnceInputType(XCTR_ID _type);

	/// <summary>
	/// ���̃L�[�����ݓ��͂���Ă��邩������
	/// </summary>
	/// <param name="_type">INPUT_TYPE�̃^�C�v</param>
	bool GetXInputType(XCTR_ID _type);

	/// <summary>
	/// ���͂���Ă���X�e�B�b�N�̒l��-32768 �` 32767�̊Ԃő���
	/// </summary>
	int GetStickRX();
	int GetStickRY();
	int GetStickLX();
	int GetStickLY();

	/// <summary>
	/// �L�[�{�[�h�̓��͂�����
	/// ��t���[���ȍ~�̓��͎͂󂯕t���Ȃ�
	/// </summary>
	/// <param name="_type">KEY_ID�̃^�C�v</param>
	bool GetKeyOnceInputType(KEY_ID _type);

	/// <summary>
	/// �L�[�{�[�h�̃L�[�����ݓ��͂���Ă��邩������
	/// </summary>
	/// <param name="_type">KEY_ID�̃^�C�v</param>
	bool GetKeyInputType(KEY_ID _type);
};
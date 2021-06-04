#pragma once

#include "../ComponentBase.h"
#include <map>

class KeyboardComponent : public ComponentBase
{
public:
	KeyboardComponent();
	~KeyboardComponent();
private:
	void Update()override;
private:
	struct Input_State
	{
		int keyType;
		int input;
	};
	//�������厖�Ȃ̂�map
	std::map<std::string, Input_State> m_key;
	//�L�[�{�[�h
	int m_input;		//���ݓ��͂���Ă���L�[���
	int m_lastInput;
public:
	//�L�[��ݒ肷��B
	//���݂͂����ݒ肵�Ȃ��ƃL�[�̎擾���o���Ȃ�
	void SetKeyBind(std::string &_keyName, int _key);
	//�L�[���������false���Ԃ�
	bool IsTrigger(std::string &_keyName);
	bool IsInput(std::string &_keyName);
};
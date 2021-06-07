#pragma once

#include "../ComponentBase.h"
#include <unordered_map>
#include <vector>
#include <functional>

class InputComponent : public ComponentBase
{
public:
	InputComponent();
	~InputComponent();
private:
	void Update()override;
private:
	struct Input_State
	{
		std::vector<int> keyType;
		std::function<void(const int)> function;
		int input;
		int num;
	};
	//�œK�������̂�umap
	std::unordered_map<std::string, Input_State> m_key;
	//�L�[�{�[�h
	int m_input;		//���ݓ��͂���Ă���L�[���
	int m_lastInput;
private:
	void InputUpdate(std::pair<const std::string, Input_State>& _it);
public:
	//�L�[��ݒ肷��B(�֐��͒ǉ����Ȃ�)
	void AddKeyBind(std::string &_keyName, int _key);
	//�L�[��ݒ肷��B(�֐��������ɒǉ�)
	void AddKeyBindFunction(std::string &_keyName, int _key, std::function<void(const int)> &_func);
	/// <summary>
	/// AddKeyBind�Ŋ��ɒǉ��ς݂̃L�[�ɓ��͒l��ǉ�����B
	/// </summary>
	/// <param name="_keyName">���͒l��ǉ�����L�[�̖��O</param>
	/// <param name="_key">�ǉ�������͒l</param>
	void AddKey(std::string &_keyName, int _key);
	/// <summary>
	/// AddKeyBind�Ŋ��ɒǉ��ς݂̃L�[�ɓ��͂��ꂽ�Ƃ��ɌĂяo�����֐���ǉ�����
	/// </summary>
	/// <param name="_keyName">���͒l��ǉ�����L�[�̖��O</param>
	/// <param name="_func">�ǉ�����֐�</param>
	void AddFunction(std::string &_keyName, std::function<void(const int)> &_func);

	/// <summary>
	/// _keyName�Ɉ�v����L�[�o�C���h���폜����
	/// </summary>
	/// <param name="_keyName">�폜����L�[�̖��O</param>
	void RemoveKeyBind(std::string& _keyName);
	//�L�[���������false���Ԃ�
	bool IsTrigger(std::string &_keyName);
	bool IsInput(std::string &_keyName);
};
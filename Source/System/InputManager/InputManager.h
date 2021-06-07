#pragma once

#include "Library/GameObject/GameObject.h"
#include <functional>

class InputComponent;
/*
�C���v�b�g�֌W��Z�߂ď�������ėp�N���X�B
���炩���ߒ�`����Ă��镨�L�[�̖��O��bootScene�̃R���X�g���N�^���Q�Ƃ��Ă�������
*/
class InputManager : public GameObject
{
public:
	InputManager(SceneBase * _scene);
	~InputManager();
private:
	void Update()override;
private:
	InputComponent* m_inputComponent;
public:
	//�L�[��ݒ肷��B(�֐��͒ǉ����Ȃ�)
	void AddKeyBind(std::string _keyName, int _key);
	//�L�[��ݒ肷��B(�֐��������ɒǉ�)
	void AddKeyBindFunction(std::string _keyName, int _key, std::function<void(const int)> _func);
	/// <summary>
	/// AddKeyBind�Ŋ��ɒǉ��ς݂̃L�[�ɓ��͒l��ǉ�����B
	/// </summary>
	/// <param name="_keyName">���͒l��ǉ�����L�[�̖��O</param>
	/// <param name="_key">�ǉ�������͒l</param>
	void AddKey(std::string _keyName, int _key);
	/// <summary>
	/// AddKeyBind�Ŋ��ɒǉ��ς݂̃L�[�ɓ��͂��ꂽ�Ƃ��ɌĂяo�����֐���ǉ�����
	/// </summary>
	/// <param name="_keyName">���͒l��ǉ�����L�[�̖��O</param>
	/// <param name="_func">�ǉ�����֐�</param>
	void AddFunction(std::string _keyName, std::function<void(const int)> _func);
	/// <summary>
	/// _keyName�Ɉ�v����L�[�o�C���h���폜����
	/// </summary>
	/// <param name="_keyName">�폜����L�[�̖��O</param>
	void RemoveKeyBind(std::string _keyName);

	//�L�[���������false���Ԃ�
	bool IsTrigger(std::string _keyName);
	bool IsInput(std::string _keyName);
};
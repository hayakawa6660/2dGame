#pragma once

#include "Library/GameObject/GameObject.h"

class InputComponent;
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
	//�L�[��ݒ肷��B
	//���݂͂����ݒ肵�Ȃ��ƃL�[�̎擾���o���Ȃ�
	void AddKeyBind(std::string _keyName, int _key);
	//KeyBind�Œǉ��������O�̃L�[�ɒǉ��ŃL�[��}������B
	void AddKey(std::string _keyName, int _key);
	//�L�[���������false���Ԃ�
	bool IsTrigger(std::string _keyName);
	bool IsInput(std::string _keyName);
};
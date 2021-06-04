#pragma once

#include "Library/GameObject/GameObject.h"

class KeyboardComponent;
class KeyboardManager : public GameObject
{
public:
	KeyboardManager(SceneBase * _scene);
	~KeyboardManager();
private:
	void Update()override;
private:
	KeyboardComponent* m_keyboard;
public:
	//�L�[��ݒ肷��B
	//���݂͂����ݒ肵�Ȃ��ƃL�[�̎擾���o���Ȃ�
	void SetKeyBind(std::string _keyName, int _key);
	//�L�[���������false���Ԃ�
	bool IsTrigger(std::string _keyName);
	bool IsInput(std::string _keyName);
};
#include "KeyboardManager.h"
#include <math.h>
#include "Library/Components/KeyboardComponent/KeyboardComponent.h"

KeyboardManager::KeyboardManager(SceneBase * _scene) :
	GameObject(_scene)
{
	m_keyboard = AddComponent<KeyboardComponent>("KeyboardComponent");
}

KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	GameObject::Update();
}

void KeyboardManager::SetKeyBind(std::string _keyName, int _key)
{
	m_keyboard->SetKeyBind(_keyName, _key);
}

bool KeyboardManager::IsTrigger(std::string _keyName)
{
	return m_keyboard->IsTrigger(_keyName);
}

bool KeyboardManager::IsInput(std::string _keyName)
{
	return m_keyboard->IsInput(_keyName);
}
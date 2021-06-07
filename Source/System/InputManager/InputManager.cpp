#include "InputManager.h"
#include <math.h>
#include "Library/Components/InputComponent/InputComponent.h"

InputManager::InputManager(SceneBase * _scene) :
	GameObject(_scene)
{
	m_inputComponent = AddComponent<InputComponent>("InputComponent");
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	GameObject::Update();
}

void InputManager::AddKeyBind(std::string _keyName, int _key)
{
	m_inputComponent->AddKeyBind(_keyName, _key);
}

void InputManager::AddKeyBindFunction(std::string _keyName, int _key, std::function<void(const int)> _func)
{
	m_inputComponent->AddKeyBindFunction(_keyName, _key, _func);
}

void InputManager::AddKey(std::string _keyName, int _key)
{
	m_inputComponent->AddKey(_keyName, _key);
}

void InputManager::AddFunction(std::string _keyName, std::function<void(const int)> _func)
{
	m_inputComponent->AddFunction(_keyName, _func);
}

void InputManager::RemoveKeyBind(std::string _keyName)
{
	m_inputComponent->RemoveKeyBind(_keyName);
}

bool InputManager::IsTrigger(std::string _keyName)
{
	return m_inputComponent->IsTrigger(_keyName);
}

bool InputManager::IsInput(std::string _keyName)
{
	return m_inputComponent->IsInput(_keyName);
}
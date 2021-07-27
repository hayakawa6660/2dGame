#include "InputComponent.h"
#include <DxLib.h>

InputComponent::InputComponent() :
	m_input(0),
	m_lastInput(true)
{
	m_key.clear();
}

InputComponent::~InputComponent()
{
	m_key.clear();
}

void InputComponent::Update()
{
	m_lastInput = m_input;
	m_input = 0;

	for (auto &it : m_key)
	{
		InputUpdate(it);
	}
}

void InputComponent::InputUpdate(std::pair<const std::string, Input_State>& _it)
{
	for (auto &key : _it.second.keyType)
		if (CheckHitKey(key) == 0)
			return;		//“ü—Í‚³‚ê‚Ä‚¢‚È‚©‚Á‚½‚ç
 	m_input |= 1 << _it.second.num;	//‚¿‚å‚Á‚Æ‹­ˆø‚É“ü—Í’l‚ðŒˆ‚ß‚éB
	if (_it.second.function) _it.second.function(m_input);
}

void InputComponent::AddKeyBind(std::string & _keyName, int _key)
{
	if (m_key.count(_keyName))		return;
	Input_State state;
	state.keyType.emplace_back(_key);
	state.num = m_key.size();
	state.input = 1 << m_key.size();	//0‚ª‚ ‚é‚½‚ß-1
	m_key.emplace(_keyName, state);
}

void InputComponent::AddKeyBindFunction(std::string & _keyName, int _key, std::function<void(const int)>& _func)
{
	if (m_key.count(_keyName))		return;
	Input_State state;
	state.keyType.emplace_back(_key);
	state.num = m_key.size();
	state.input = 1 << m_key.size();	//0‚ª‚ ‚é‚½‚ß-1
	state.function = _func;
	m_key.emplace(_keyName, state);
}

void InputComponent::AddKey(std::string & _keyName, int _key)
{
	if (!m_key.count(_keyName))		return;
	m_key[_keyName].keyType.emplace_back(_key);
}

void InputComponent::AddFunction(std::string & _keyName, std::function<void(const int)>& _func)
{
	if (!m_key.count(_keyName))		return;
	m_key[_keyName].function = _func;
}

void InputComponent::RemoveKeyBind(std::string & _keyName)
{
	if (!m_key.count(_keyName))		return;
	m_key.erase(_keyName);
}

bool InputComponent::IsTrigger(std::string & _keyName)
{
	if (!m_key.count(_keyName)) return false;
	return (((~m_lastInput & m_input) & m_key[_keyName].input) != 0);
}

bool InputComponent::IsInput(std::string & _keyName)
{
	if (!m_key.count(_keyName)) return false;
	return ((m_input & (int)m_key[_keyName].input) != 0);
}
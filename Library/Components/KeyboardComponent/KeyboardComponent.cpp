#include "KeyboardComponent.h"
#include <DxLib.h>

KeyboardComponent::KeyboardComponent() :
	m_input(0),
	m_lastInput(true)
{
	m_key.clear();
}

KeyboardComponent::~KeyboardComponent()
{
	m_key.clear();
}

void KeyboardComponent::Update()
{
	m_lastInput = m_input;
	m_input = 0;

	int a = 0;
	for (auto &it : m_key)
	{
		if (CheckHitKey(it.second.keyType) != 0)
			m_input |= 1 << a;	//‚¿‚å‚Á‚Æ‹­ˆø‚É“ü—Í’l‚ðŒˆ‚ß‚éB
		a++;
	}
}

void KeyboardComponent::SetKeyBind(std::string & _keyName, int _key)
{
	m_key[_keyName].keyType = _key;
	m_key[_keyName].input = 1 << (m_key.size() - 1);	//0‚ª‚ ‚é‚½‚ß-1
}

bool KeyboardComponent::IsTrigger(std::string & _keyName)
{
	if (!m_key.count(_keyName)) return false;
	return (((~m_lastInput & m_input) & m_key[_keyName].input) != 0);
}

bool KeyboardComponent::IsInput(std::string & _keyName)
{
	if (!m_key.count(_keyName)) return false;
	return ((m_input & (int)m_key[_keyName].input) != 0);
}

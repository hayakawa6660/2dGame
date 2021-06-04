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
	//順序が大事なのでmap
	std::map<std::string, Input_State> m_key;
	//キーボード
	int m_input;		//現在入力されているキー情報
	int m_lastInput;
public:
	//キーを設定する。
	//現在はこれを設定しないとキーの取得が出来ない
	void SetKeyBind(std::string &_keyName, int _key);
	//キーが無ければfalseが返る
	bool IsTrigger(std::string &_keyName);
	bool IsInput(std::string &_keyName);
};
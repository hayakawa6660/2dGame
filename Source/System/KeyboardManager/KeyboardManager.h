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
	//キーを設定する。
	//現在はこれを設定しないとキーの取得が出来ない
	void SetKeyBind(std::string _keyName, int _key);
	//キーが無ければfalseが返る
	bool IsTrigger(std::string _keyName);
	bool IsInput(std::string _keyName);
};
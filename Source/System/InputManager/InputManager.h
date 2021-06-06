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
	//キーを設定する。
	//現在はこれを設定しないとキーの取得が出来ない
	void AddKeyBind(std::string _keyName, int _key);
	//KeyBindで追加した名前のキーに追加でキーを挿入する。
	void AddKey(std::string _keyName, int _key);
	//キーが無ければfalseが返る
	bool IsTrigger(std::string _keyName);
	bool IsInput(std::string _keyName);
};
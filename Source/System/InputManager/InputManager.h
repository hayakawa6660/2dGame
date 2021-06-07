#pragma once

#include "Library/GameObject/GameObject.h"
#include <functional>

class InputComponent;
/*
インプット関係を纏めて処理する汎用クラス。
あらかじめ定義されている物キーの名前はbootSceneのコンストラクタを参照してください
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
	//キーを設定する。(関数は追加しない)
	void AddKeyBind(std::string _keyName, int _key);
	//キーを設定する。(関数も同時に追加)
	void AddKeyBindFunction(std::string _keyName, int _key, std::function<void(const int)> _func);
	/// <summary>
	/// AddKeyBindで既に追加済みのキーに入力値を追加する。
	/// </summary>
	/// <param name="_keyName">入力値を追加するキーの名前</param>
	/// <param name="_key">追加する入力値</param>
	void AddKey(std::string _keyName, int _key);
	/// <summary>
	/// AddKeyBindで既に追加済みのキーに入力されたときに呼び出される関数を追加する
	/// </summary>
	/// <param name="_keyName">入力値を追加するキーの名前</param>
	/// <param name="_func">追加する関数</param>
	void AddFunction(std::string _keyName, std::function<void(const int)> _func);
	/// <summary>
	/// _keyNameに一致するキーバインドを削除する
	/// </summary>
	/// <param name="_keyName">削除するキーの名前</param>
	void RemoveKeyBind(std::string _keyName);

	//キーが無ければfalseが返る
	bool IsTrigger(std::string _keyName);
	bool IsInput(std::string _keyName);
};
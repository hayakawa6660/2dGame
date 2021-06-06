#pragma once

#include "../ComponentBase.h"
#include <map>
#include <vector>

/*
#if 0
class InputComponent : public ComponentBase
{
public:
	//XBOXコントローラーのID
	enum class XCTR_ID : int
	{
		A		=	1 << 0,
		B		=	1 << 1,
		X		=	1 << 2,
		Y		=	1 << 3,
		UP		=	1 << 4,
		DOWN	=	1 << 5,
		RIGHT	=	1 << 6,
		LEFT	=	1 << 7,
		LB		=	1 << 8,
		RB		=	1 << 9,
		START	=	1 << 10,
		SELECT	=	1 << 11,
		RSTICK	=	1 << 12,
		LSTICK	=	1 << 13,
	};

	//キーボードのID
	enum class KEY_ID : int
	{
		UP		= 1 << 0,
		DOWN	= 1 << 1,
		RIGHT	= 1 << 2,
		LEFT	= 1 << 3,
		W		= 1 << 4,
		A		= 1 << 5,
		S		= 1 << 6,
		D		= 1 << 7,
		ALT		= 1 << 8,
		CTRL	= 1 << 9,
		SHIFT	= 1 << 10,
		SPACE	= 1 << 11,
		ESC		= 1 << 12,
	};

public:
	InputComponent();
	~InputComponent();
private:
	void Update()override;

	void XCtrUpdate();

	void KeyUpdate();
private:
	//XBOXコントローラー
	int m_xInput;
	int m_xLastInput;
	XINPUT_STATE m_xState;
	int m_controllerNum;
	//キーボード
	int m_keyInput;
	int m_keyLastInput;
public:
	/// <summary>
	/// 何個目のコントローラーかをセットする
	/// 主にプレイヤーが複数いる場合で使う
	/// </summary>
	void SetControllerNum(int _num) { m_controllerNum = _num; }

	/// <summary>
	/// XBOXコントローラーの入力され始めを取得する
	/// 二フレーム以降の入力は受け付けない
	/// </summary>
	/// <param name="_type">INPUT_TYPEのタイプ</param>
	bool GetXOnceInputType(XCTR_ID _type);

	/// <summary>
	/// そのキーが現在入力されているかを見る
	/// </summary>
	/// <param name="_type">INPUT_TYPEのタイプ</param>
	bool GetXInputType(XCTR_ID _type);

	/// <summary>
	/// 入力されているスティックの値を-32768 ～ 32767の間で送る
	/// </summary>
	int GetStickRX();
	int GetStickRY();
	int GetStickLX();
	int GetStickLY();

	/// <summary>
	/// キーボードの入力を見る
	/// 二フレーム以降の入力は受け付けない
	/// </summary>
	/// <param name="_type">KEY_IDのタイプ</param>
	bool GetKeyOnceInputType(KEY_ID _type);

	/// <summary>
	/// キーボードのキーが現在入力されているかを見る
	/// </summary>
	/// <param name="_type">KEY_IDのタイプ</param>
	bool GetKeyInputType(KEY_ID _type);
};
#endif
*/

class InputComponent : public ComponentBase
{
public:
	InputComponent();
	~InputComponent();
private:
	void Update()override;
private:
	struct Input_State
	{
		std::vector<int> keyType;
		int input;
	};
	//順序が大事なのでmap
	std::map<std::string, Input_State> m_key;
	//キーボード
	int m_input;		//現在入力されているキー情報
	int m_lastInput;
private:
	void InputUpdate(std::pair<const std::string, Input_State>& _it, int _num);
public:
	//キーを設定する。
	//現在はこれを設定しないとキーの取得が出来ない
	void AddKeyBind(std::string &_keyName, int _key);
	void AddKey(std::string &_keyName, int _key);
	//キーが無ければfalseが返る
	bool IsTrigger(std::string &_keyName);
	bool IsInput(std::string &_keyName);
};
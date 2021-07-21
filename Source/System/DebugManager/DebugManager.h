#pragma once

#include "Library/GameObject/GameObject.h"

#define DEBUG 1

#if DEBUG
#include <vector>
#include <iostream>
#include <map>

class DebugClasses;

class DebugManager : public GameObject
{
public:
	DebugManager(SceneBase* _scene);
	~DebugManager();

private:
	void Update()override;
private:
	std::map<std::string, bool> m_active;

	bool m_isDebugMode;
	std::list<DebugClasses*> m_debugList;

	int m_menuNum;		//DebucClassを何個生成したか
	int m_currentNum;	//現在選んでいるメニュー

	bool m_allDestroy;
private:
	void SelectUpdate();
	void ResetUpdate();
	void DestroyUpdate();
public:

	void SetActive(std::string &_className, bool _active);
	void Puts(int _x, int _y, std::string _classTag, const char * _format, ...);

	//void VSOutputLog(const char* _format, ...);
	/*
	{
#if _DEBUG
		va_list vlist;
		va_start(vlist, _format);
		char ch[256];
		vsprintf_s(ch, _format, vlist);
		OutputDebugString(ch);
		OutputDebugString("\n");
		va_end(vlist);
#endif
	}

	void DebugManager::VSOutputLog(const char* _format, const VECTOR& _vec)
	{
#if _DEBUG
		std::string str = std::string(_format) + "(%f.%f,%f)";
		VSOutputLog(str.c_str(), _vec.x, _vec.y, _vec.z);
#endif
	}
	*/
	/// <summary>
	/// 現在までに作ったデバックのクラスを全て消す
	/// </summary>
	void ListAllClear();

	/// <summary>
	/// 送った名前の要素が登録されていれば、そのbool値を返す
	/// 無ければ必ずfalseが返ってきて、要素は追加されないので注意
	/// </summary>
	/// <param name="_factorName">デバックメニューにした名前</param>
	bool GetFactorFlag(std::string _factorName);
};


//※デバックメニューの呼び出し方
//XBoxコントローラーで、Start + Select + LB + RB同時押しもしくは
//キーボードでCtrl + Alt同時押しで開きます
//開いた後は、それぞれ上下キー(ボタン)でメニューを選択して、
//右キー(ボタン)で決定、解除します
namespace Debug
{
	/// <summary>
	/// ラグ等でデバックのメニューを操作するのが厳しい場合の関数
	/// </summary>
	/// <param name="_classTag">Activeをセットするデバッククラス名</param>
	void SetActive(std::string _className, bool _active);

	/// <summary>
	/// ラグ等でデバックのメニューを操作するのが厳しい場合の関数
	/// </summary>
	/// <param name="_format">デバッグログを表示する。</param>
	void VSOutputLog(const char* _format...);

	/// <summary>
	/// 送った値を全て表示する
	/// </summary>
	/// <param name="_x">表示したい文字のX座標</param>
	/// <param name="_y">表示したい文字のY座標</param>
	/// <param name="_classTag">生成するデバッククラス名</param>
	/// <param name="_format">ファイルのパス</param>
	void DebugPrintf(int _x, int _y, std::string _classTag, const char *_format...);

	/// <summary>
	/// 送った名前の要素が登録されていれば、そのbool値を返す
	/// 無ければ要素を追加してチェックする。
	/// 一度目の作成段階では必ずfalseが返ってくるので注意
	/// </summary>
	/// <param name="_factorName">デバックメニューにした名前</param>
	bool GetFactorFlag(std::string _factorName);
	/// <summary>
	/// 生成したデバックメニューのリストをすべて削除する
	/// 主に要素数を増やす過ぎないためにシーンの切り替え時に使う
	/// </summary>
	void ListAllClear();
};
#endif
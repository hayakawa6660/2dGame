#pragma once
#include "Library/GameObject/GameObject.h"
#include <windows.h>
#include <shlobj.h>
#include <unordered_map>
#include <mutex>

/*
****************使い方、手順*****************
※※※※※※※※※ 注意 ※※※※※※※※※
ゲーム中にオブジェクトを読み込む場合、対応したSceneのNew関数の中で
Zip解凍をして、モデルをあらかじめロードする所までしておいてください。後々でやると

thread を使ってクラスをnew
↓
zip解凍が終わるまでLoad関数を待機させる別処理
↓
Load関数でResourceLoad依頼
↓
Resourceのロードが終わるまでStart関数を待機させる別処理
↓
Start関数でリソースをゲットする。

という手順を踏むことになり大変面倒くさいことになります。
Update関数でState分けをする手もありますが、どのみち別処理書かないといけないので
面倒くさいですし...
※※※※※※※※※

**********************  正式手順  *************************
クラスをnewする
↓
コンストラクタでジップ解凍依頼を出す
↓
Load()関数 : リソースマネージャーにロード依頼
↓
Start() : GetHandleを使用してリソースを取得する
*/

class CompressManager : public GameObject
{
public:
	CompressManager(GameObject * _scene);
	~CompressManager();
private:
	//Zip解凍関数本体(呼び出しはUnCompress)
	bool Unzip(IShellDispatch *_pShellDispatch, WCHAR *_lpszZipPath, WCHAR *_lpszOutPath);
	//Unicode文字列変換関数(IShellがUnicodeのみ対応のため)
	int CharToWchart(const char * _pSrc, wchar_t *_pDest, const size_t _sDestSize);
public:
	void AllDeleteDirectory();
	/// <summary>
	/// <para> フォルダ(ディレクトリ)を解凍する。</para>
	/// </summary>
	/// <param name="_zipPath">解凍したいzipFileのパス</param>
	/// <param name="_outPath">解凍したzipFileを保存するフォルダ(ディレクトリ)名</param>
	bool UnCompress(const char *_zipPath, const char *_outPath);

	/// <summary>
	/// <para>フォルダ(ディレクトリ)を削除する。</para>
	/// <para>このプロジェクトで生成したファイルは自動的に削除されますが、</para>
	/// <para>ブレークポイントやNULLエラーなどで強制終了した場合はこの関数が呼び出されない可能性があるので</para>
	/// <para>プログラムが完成した後にZip化をして、ロードする処理をすることを推奨します</para>
	/// <para>※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※</para>
	/// <para>プログラムで削除するため、取り消し、やり直しができない可能性があります。</para>
	/// <para>使用時はそのファイルが本当に消してもいいフォルダなのかご確認の上使用ください。</para>
	/// <para>※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※</para>
	/// </summary>
	/// <param name="lpPathName">削除したいフォルダの名前</param>
	bool DeleteDirectory(LPCTSTR _lpPathName);

	bool IsUnZip(std::string _outPath);

	bool IsAllUnZip();
private:
	std::mutex m_mutex;
	char m_currentDirectory[256];
	IShellDispatch *m_pShellDispatch;	//Shell起動用構造体
	std::unordered_map<std::string, bool> m_outFilePath;	//終了時zip解凍したファイルは全部消すため、回答した場所を保存しておく
};

#if 0
#include "Library/GameObject/GameObject.h"
#include <stdio.h>

class CompressManager : public GameObject
{
public:
	CompressManager(GameObject * _scene);
	~CompressManager();

public:
	void Compress(const char *_infile, const char *_outfile);
	void UnCompress(const char * _infile, const char * _outfile);
private:

	static const int INBUFSIZ = 1024;	/* 入力バッファサイズ（任意） */
	static const int OUTBUFSIZ = 1024;	/* 出力バッファサイズ（任意） */

	char m_inbuf[INBUFSIZ];           /* 入力バッファ */
	char m_outbuf[OUTBUFSIZ];         /* 出力バッファ */
};

#endif
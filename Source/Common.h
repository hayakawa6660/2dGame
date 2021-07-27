#pragma once

#include <string>
#include <MyDxLib.h>
#include <functional>

/// <summary>
/// 画像データに必要な物の入っている構造体
/// std::string	fileName	= モデルの入っているフォルダの名前(ResourceManagerからの検索でも使う)
/// int			handle		= 読み込んだモデルのハンドル格納用変数
struct Model_Info
{
	std::string fileName;
	int handle;
	Model_Info() :
		fileName(""), handle(-1)
	{}
};

/// <summary>
/// 画像データに必要な物の入っている構造体
/// 画像データはハンドラーの情報を書き換えて動かす形ではないので、内部でfunctionを含んでいます。
/// std::string		fileName	= 画像の入っているフォルダの名前
/// VECTOR			position	= 画像の2Dポジション(Zは描画順に関係している。大きければ手前に来る)
/// int				handle		= 読み込んだ画像のハンドル格納用変数
/// int				sizeX		= 画像のX方向サイズ
/// int				sizeY		= 画像のY方向サイズ
/// float			alpha		= 画像の透明度
/// std::function	function	= 画像を描画する関数。使い方はFadeManagerを参考にしてください。
struct Sprite_Info
{
	std::string fileName;
	VECTOR position;
	int handle;
	int sizeX, sizeY;
	float alpha;
	Sprite_Info() :
		fileName(""), position(VGet(0, 0, 0)), handle(-1), sizeX(0), sizeY(0), alpha(1.f)
	{}
};

/// サウンド系統に必要な情報をまとめた構造体
struct Sound_Info
{
	std::string fileName;
	int handle;
	bool isLoop;
	int volume;
	Sound_Info() :
		fileName(""), handle(-1),
		isLoop(false), volume(255)
	{}
};

/// テキストを表示させるために必要な情報
struct Text_Info
{
	std::string text;
	VECTOR position;
	int color;
};
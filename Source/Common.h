#pragma once

#include <string>
#include <MyDxLib.h>

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
/// std::string	fileName	= 画像の入っているフォルダの名前
/// int			handle		= 読み込んだ画像のハンドル格納用変数
/// int			sizeX		= 画像のX方向サイズ
/// int			sizeY		= 画像のY方向サイズ
struct Sprite_Info
{
	std::string fileName;
	int handle;
	int sizeX, sizeY;
};

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

struct Time {
	//値が多いとオーバーフローして0になるのでdouble型
	double deltaTime;	//前回時間からの差	※いろんなところに渡すので容量削減のためconstで参照渡しをする
	double oldTime;	//前のフレーム
	double nowTime;	//ゲーム開始からの時刻
};

enum Direction {
	LEFT = 0,
	RIGHT,
};
//ガードの情報
struct GuardCollision_Info {
	bool isGuard;		//ガードしているか
	bool isJustGuard;	//ジャストガードできたか

	int model;

	VECTOR myPos;
	VECTOR guardPos;	//ガードの一番上

	float radius;		//ガードとプレイヤーの半径
	GuardCollision_Info() :isGuard(false), isJustGuard(false),
		model(-1), myPos{ 0.0f,0.0f,0.0f }, guardPos{ 0.0f,0.0f,0.0f },
		radius(0.0f){}
};

enum HIT_INFO {//ヒットした時の状態
	NO_HIT = 0,
	HIT,
	GUARD,
};
//攻撃時のコライダー情報
struct Attack_Info {
	VECTOR top;
	VECTOR bottom;
	float radius;
	Attack_Info() :top{ 0,0,0 }, bottom{ 0,0,0 }, radius(0.0f){}
};
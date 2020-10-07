#pragma once

#include <string.h>

namespace BossDefine
{
	//グラフィッカーはアニメーションを追加したら
	//自身で順番通りに説明込みで挿入すること
	//名前は、英語で書くこと。
	//長くなりすぎないように注意すること(多くても３単語)
	enum class ANIM_STATE
	{
		STAY = 0,			//待機
		WALK,				//移動
		SCARED,				//怯み
		ATTACK_1,			//左手攻撃
		ATTACK_2,			//右手チェーンソー振り下ろし
		ATTACK_2_END,		//右手チェーンソー終わり

		//アニメーション不足のため、薙ぎ払いのみを使うため切り分け
		//繋ぎや挙動が少し変になるのはバランス調整のためご愛嬌
		ATTACK_3_START,		//突進攻撃開始
		ATTACK_3_LOOP,		//突進攻撃移動中
		ATTACK_3_CREAVE,	//突進攻撃薙ぎ払い
		ATTACK_3_END,		//突進攻撃終わり

		ATTACK_4_START,		//ジャンプ攻撃
		ATTACK_4_LOOP,		//ジャンプ空中
		ATTACK_4_LANDING,	//着地
		ATTACK_4_END,		//終了→待機以降

		BACKJUMP_START,		//通常ジャンプ開始
		BACKJUMP_LOOP,		//通常ジャンプループ
		BACKJUMP_LANDING,	//着地
		BACKJUMP_END,		//終了→待機以降

		DEAD,
		MAX,			//終了。必ず一番最後。消さないこと！
	};
	static constexpr float STAY_TIME = 3.f * 60.f;

	//歩きで攻撃一段目が当たる場所までの距離
	static constexpr float MOVE_RANGE = 800.f;
	//AIの切り替わるの基準
	static constexpr float AI_STAY_RANGE = 800.f;
	static constexpr float AI_JUMP_RANGE = 2000.f;

	//ATTACK_1の当たり判定開始タイミング
	static constexpr float AT1_COLISION_START = 20.f;
	//ATTACK_1の当たり判定終了タイミング
	static constexpr float AT1_COLISION_END = 50.f;

	//ATTACK_2の当たり判定開始タイミング
	static constexpr float AT2_COLISION_START = 46.f;
	//ATTACK_2の当たり判定終了タイミング
	static constexpr float AT2_COLISION_END = 65.f;

	//ATTACK_3の当たり判定開始タイミング
	static const int AT3_LOOP_TIME = 40;
	static constexpr float AT3_COLISION_START = 13.f;
	//ATTACK_1の当たり判定終了タイミング
	static constexpr float AT3_COLISION_END = 18.f;
	//ジャンプの初速
	static constexpr float JUMP_FIRST_SPEED = 40.f;
}
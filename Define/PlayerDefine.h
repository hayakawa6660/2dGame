#pragma once

namespace PlayerDefine {

	enum Direction {
		LEFT = 0,
		RIGHT,
	};

	//////////////////////////////////////
	//HP,SP
	//////////////////////////////////////
	static constexpr int MAX_HIT_POINT = 100;
	static constexpr int MAX_STAMINA_POINT = 1000;
	///////////////////////////////////////////
	//通常移動
	///////////////////////////////////////////
	static constexpr float MOVE_NORMAL_SPEED = 8.0f;
	static constexpr float MOVE_NORMAL_DECELERATION = 0.93f;
	static constexpr float MOVE_CORRECTION_SPEED = 0.4f;
	///////////////////////////////////////
	//ダッシュ
	///////////////////////////////////////
	static constexpr float MOVE_DASH_SPEED = 15.0f;
	static constexpr float MOVE_DASH_DECELERATION = 0.90f;
	///////////////////////////////////////
	//ガード
	///////////////////////////////////////
	static constexpr int JUST_GUARD_FLAME = 10;

	///////////////////////////////////////
	//溜め攻撃
	//////////////////////////////////////
	static constexpr float CHARGE_ATTACK_RANGE = 80.0f;
	static constexpr float CHARGE_ATTACK_RADIUS = 45.0f;
	//溜め時間
	static constexpr int CHARGE_ATTACK_TIME = 100;
	//溜め攻撃力
	static constexpr int CHARGE_ATTACK_DAMAGE = 130;
	///////////////////////////////////////
	//コンボ攻撃
	//////////////////////////////////////
	static constexpr float COMBO_ATTACK_RANGE = 75.0f;
	static constexpr int COMBO_ATTACK_DAMAGE[] = {
		10,
		15,
		20,
		35,
		40
	};
}

/*
namespace PlayerDefine
{
	enum class ANIM_STATE
	{
		STAY = 0,
		WALK,
		DASH,
		END,
	};
	enum class STATE
	{
		STAY = 0,
		WALK,
		DASH,
		COMBO_ATTACK,
		END,
	};

	static constexpr float WALK_MAX_SPEED = 5.f;
	static constexpr float DASH_MAX_SPEED = 10.f;

	//走りの慣性
	static constexpr float INERTIA = 1.2f;
	//減速率
	static constexpr float DECELERATION = 0.8f;
}
*/
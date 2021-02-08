#pragma once

#include "../UiBase.h"
#include "../../../Common.h"

#include <unordered_map>
#include <string>
#include <assert.h>
#include <DxLib.h>

class PlayerUi : public UiBase {
public:
	enum TYPE {
		HP_BAR = 0,
		DAMAGE_BAR,
		STAMINA_BAR,
		BAR_BACK,
	};
	PlayerUi(SceneBase * _scene);
	~PlayerUi();
	void Update()override;
	void Draw()override;

	void Create(const TYPE& _type, const char* _p);
	void SetHitPiintInfo(const int& _currentHp, const int & _maxHp);
	void SetStaminaInfo(const int& _currentStamina, const int & _maxStamina);
private:
	void LoadEndCheck();
private:
	struct BarInfo {
		float val;
		float maxVal;
		VECTOR pos;
		float size;
		BarInfo() :val(1), maxVal(1), pos{ 0,0,0 }, size(0.f) {}
	};
	BarInfo m_hpBar;
	BarInfo m_damage;
	BarInfo m_staminaBar;
	int m_decreaseCount;
	int m_addCount;
	bool m_isLoadEnd;
	bool m_active;
	std::unordered_map<TYPE, Sprite_Info> m_ui;
public:
	void SetAcive(bool _active) { m_active = _active; }
};
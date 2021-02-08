#pragma once

#include "../UiBase.h"
#include <array>
#include <string>
#include <assert.h>
#include <DxLib.h>

class EnemyUi : public UiBase {
public:
	enum class TYPE {
		HP_BAR = 0,
		BACK,
		DAMAGE,
		MAX,
	};
	EnemyUi(SceneBase * _scene);
	~EnemyUi();
private:
	void Update()override;
	void Draw()override;
	void LoadUpdate();
public:
	void Reset(int _hp);
	void SetHitPointInfo(const int& _currentHp);

private:
	struct BarInfo {
		std::string fileName;
		int texture;
		int maxHp;
		int currentHp;
		float whidhtHarf;
		VECTOR texSize;
		VECTOR pos;
	};
	std::array<BarInfo, (int)TYPE::MAX> m_bar;

	int m_decreaseCount;
	int m_nextHp;
	bool m_isLoadEnd;
};
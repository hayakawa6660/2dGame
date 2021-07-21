#pragma once

#include "../EffectBase.h"
#include <array>

class FireFlowarEffect : public EffectBase {
public:
	FireFlowarEffect(SceneBase * _scene);
	~FireFlowarEffect();
	void Start()override;
	void Update()override;

private:
	void ChildCreate(int _num);
private:
	static const int CHILD_NUM = 10;

	//ƒƒCƒ“‚Ìƒ‰ƒCƒt
	float m_lifeTime;
	int m_spawnCount;
	struct ChildState {
		VECTOR position;
		float alpha;
		MATRIX angle;
		float upPowor;
		bool active;
		bool fadeOut;
		float rotation;
	};
	std::array<ChildState, CHILD_NUM> m_child;
};
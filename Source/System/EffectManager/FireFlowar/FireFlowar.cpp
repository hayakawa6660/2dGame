#include "FireFlowar.h"

FireFlowarEffect::FireFlowarEffect(SceneBase * _scene) :
	EffectBase(_scene)
{
}

FireFlowarEffect::~FireFlowarEffect()
{
}

void FireFlowarEffect::Start()
{
	m_spawnCount = 0;
	for (auto &it : m_child)
	{
		it.alpha = 255.f;
		it.position = EffectBase::GetPosition();
		it.upPowor = (float)GetRand(15);
		it.active = false;
	}
	m_lifeTime = 100.f;
	ChildCreate(1);
}

void FireFlowarEffect::Update()
{
	if (--m_spawnCount <= 0)
	{
		m_spawnCount = GetRand(5);
		int spawnNum = GetRand(5);
		ChildCreate(spawnNum);
	}

	int a = 0;
	for (auto &it : m_child)
	{
		if (!it.active)
			continue;
		it.upPowor -= 0.3f;
		it.position.y += it.upPowor;
		VECTOR velocity = VGet(0, 0, 20.f);
		VECTOR move = VTransform(velocity, it.angle);
		it.position += move;
		if (!it.fadeOut) {
			it.alpha += 10.f;
			if (it.alpha >= 255.f)
			{
				it.fadeOut = true;
			}
		}
		else
		{
			if (it.alpha >= 0) {
				it.alpha -= 30.f;
			}
		}
		a++;
	}
	if (m_child.back().alpha < 0)
	{
		EffectBase::Destroyed();
	}
}

/*
void FireFlowarEffect::Draw()
{
	for (auto &it : m_child)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)it.alpha);
		SetDrawBright(255, 100, 0);
		DrawBillboard3D(it.position, 0.5f, 0.5f, 36, it.rotation, EffectBase::GetTexture().handle, true);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
*/

void FireFlowarEffect::ChildCreate(int _num)
{
	int num = 0;
	for (auto &it : m_child)
	{
		if (it.active == true)
			continue;
		it.position = EffectBase::GetPosition();
		it.alpha = 0.f;
		it.active = true;
		it.fadeOut = false;
		it.rotation = (float)GetRand(314) / 100.f;
		float randAngle = ((((float)GetRand(314 / 2) + 0.01f) / 100.f) - ToRadian(90.f));
		it.angle = MMult(EffectBase::GetMatrix(), MGetRotY(randAngle));
		num++;
		if (num >= _num)
			break;
	}
}
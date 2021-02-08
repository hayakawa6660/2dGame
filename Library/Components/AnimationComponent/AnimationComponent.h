#pragma once

#include "../ComponentBase.h"

//アニメーションがあるものは自身のクラスの下にこのクラスを継承
//して使う
class AnimationComponent : public ComponentBase
{
public:
	AnimationComponent();
	~AnimationComponent();
private:
	void Start()override{}
	void Update()override;
	void NormalUpdate();

	void BlendUpdate();
public:
	void BlendRateSpeed(const float& _blendSpeed) { m_blend.speed = _blendSpeed; }

	bool PlayingEnd();
	virtual bool PlayingAnimTypeEnd(const int& _handle);

	int GetCurrentAnimHandle();
	float GetTotalTime();
	float GetCurrentAnimTime();

	void Play(const int& _animHandle, const float& _speed = 0.5f);
	void SetBlendFlag(bool _flag) { m_blendFlag = _flag; }
	void SetPlaySpeed(const float& _speed);
	void SetBlendSpeed(const float& _speed);
	void Stop(bool _stop) { m_stop = _stop; }
	void SetBody(int _model) { m_model = _model; }
	void SetReverce(bool _flag) { m_reverse = _flag; }
private:
	int		m_model;
	int		m_nextAnim;		//一時的にモデルのハンドルを保管
	int		m_currentAnim;	//今再生しているアニメーションのハンドル
	int		m_currentIndex;	//アニメーションした後
	float	m_playSpeed;	//アニメーションのスピード
	float	m_currentTime;	//今のアニメーションのフレーム	
	float	m_totalTime;	//アタッチされたアニメーションの総フレーム
	bool	m_blendFlag;
	bool	m_stop;			//アニメーションをストップするかどうか
	bool	m_reverse;		//逆再生させるかどうか

	struct BLEND_ANIM_INFO {
		int		index;		//アニメーションする前
		float	rate;		//ブレンド率
		float	speed;
		BLEND_ANIM_INFO() :
			index(-1), rate(0.f), speed(0.2f) {}
	};
	BLEND_ANIM_INFO m_blend;
};
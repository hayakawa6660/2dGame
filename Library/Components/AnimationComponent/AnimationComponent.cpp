#include "AnimationComponent.h"
#include <assert.h>
#include <DxLib.h>

AnimationComponent::AnimationComponent() :
	m_model(-1),
	m_currentAnim(-1),
	m_nextAnim(-1),
	m_currentIndex(-1),
	m_playSpeed(0.0f),
	m_currentTime(0.0f),
	m_totalTime(0.0f),
	m_stop(false),
	m_blendFlag(false),
	m_reverse(false),
	m_prevPos(VGet(0, 0, 0))
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Update()
{
	if (m_stop)
		return;
	if (m_nextAnim == -1)
		return;
	//ブレンドであればブレンドのUpdateに入る
	if (m_blendFlag)
		BlendUpdate();
	else
		NormalUpdate();

	if (!m_reverse)
	{
		if (m_currentTime + m_playSpeed > m_totalTime) {
			m_currentTime -= m_totalTime - m_playSpeed;
			m_prevPos = VGet(0, 0, 0);
		}
		else {
			m_currentTime += m_playSpeed;
		}
	}
	else
	{
		if (m_currentTime - m_playSpeed < 0.f) {
			m_currentTime += m_totalTime + m_playSpeed;
			m_prevPos = VGet(0, 0, 0);
		}
		else {
			m_currentTime -= m_playSpeed;
		}
	}

	MV1SetAttachAnimTime(m_model, m_currentIndex, m_currentTime);
}

void AnimationComponent::NormalUpdate()
{
	if (m_currentAnim != m_nextAnim) {
		if (m_currentIndex >= 0)
			MV1DetachAnim(m_model, m_currentIndex);
		m_currentIndex = MV1AttachAnim(m_model, 0, m_nextAnim);
		m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_currentIndex);
		m_currentAnim = m_nextAnim;
	}
}

void AnimationComponent::BlendUpdate()
{
	if (m_currentAnim != m_nextAnim && m_blend.rate == 0.0f) {
		m_prevPos = VGet(0, 0, 0);
		m_blend.index = m_currentIndex;
		m_currentIndex = MV1AttachAnim(m_model, 0, m_nextAnim);
		m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_currentIndex);
		m_blend.rate = m_currentAnim == -1 ? 0.0f : 1.0f;//一番最初のアニメーションはブレンド率を0.0fにする
		m_currentTime = 0.0f;
		m_currentAnim = m_nextAnim;
	}
	if (m_blend.index != -1) {
		if (m_blend.rate > 0.0f) {//ブレンド中
			MV1SetAttachAnimBlendRate(m_model, m_blend.index, m_blend.rate);
			MV1SetAttachAnimBlendRate(m_model, m_currentIndex, 1.0f - m_blend.rate);
			m_blend.rate -= m_blend.speed;
		}
		else {
			MV1DetachAnim(m_model, m_blend.index);
			m_blend.index = -1;
			m_blend.rate = 0.0f;
		}
	}
}

bool AnimationComponent::PlayingEnd()
{
	return m_currentTime + m_playSpeed >= m_totalTime;
}//ブレンドが終了したら前のアニメーションをデタッチ

bool AnimationComponent::PlayingAnimTypeEnd(const int & _handle)
{
	return m_currentAnim == _handle && PlayingEnd();
}

int AnimationComponent::GetCurrentAnimHandle()
{
	return m_currentAnim;
}

float AnimationComponent::GetTotalTime()
{
	return m_totalTime;
}

float AnimationComponent::GetCurrentAnimTime()
{
	return m_currentTime;
}

void AnimationComponent::Play(const int & _animHandle, const float & _speed)
{
	m_nextAnim = _animHandle;
	m_playSpeed = _speed;
}

void AnimationComponent::SetPlaySpeed(const float & _speed)
{
	m_playSpeed = _speed;
}

void AnimationComponent::SetBlendSpeed(const float & _speed)
{
	m_blend.speed = _speed;
}

VECTOR AnimationComponent::GetFramePosition(const std::string &_frameName)
{
	int root = MV1SearchFrame(m_model, _frameName.c_str());
	return MV1GetAttachAnimFrameLocalPosition(m_model, m_currentAnim, root);
}

VECTOR AnimationComponent::GetMoveFrame(const std::string & _frameName, bool _fixed)
{
	int frame = MV1SearchFrame(m_model, _frameName.c_str());
	VECTOR pos = MV1GetAttachAnimFrameLocalPosition(m_model, m_currentAnim, frame);
	VECTOR velocity = pos - m_prevPos;
	m_prevPos = pos;
	if(_fixed)	MV1SetFrameUserLocalMatrix(m_model, frame, MGetIdent());
	return velocity;
}

void AnimationComponent::GetFrameZeroVector(const std::string & _frameName)
{
	int frame = MV1SearchFrame(m_model, _frameName.c_str());
	MV1SetFrameUserLocalMatrix(m_model, frame, MGetIdent());
}

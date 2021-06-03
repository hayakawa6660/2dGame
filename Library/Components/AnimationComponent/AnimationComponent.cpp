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
	m_prevPos(VGet(0, 0, 0)),
	m_animVelocity(VGet(0, 0, 0)),
	m_animPosition(VGet(0, 0, 0))
{
	m_animList.clear();
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
	//�u�����h�ł���΃u�����h��Update�ɓ���
	if (m_blendFlag)
		BlendUpdate();
	else
		NormalUpdate();

	bool isLoop = false;
	if (!m_reverse)
	{
		if (m_currentTime + m_playSpeed > m_totalTime) {
			m_currentTime -= m_totalTime - m_playSpeed;
			isLoop = true;
		}
		else {
			m_currentTime += m_playSpeed;
		}
	}
	else
	{
		if (m_currentTime - m_playSpeed <= 0.f) {
			m_currentTime += m_totalTime + m_playSpeed;
			isLoop = true;
		}
		else {
			m_currentTime -= m_playSpeed;
		}
	}

	MV1SetAttachAnimTime(m_model, m_currentIndex, m_currentTime);

	if (m_rootName.size() != 0)
	{
		int frame = MV1SearchFrame(m_model, m_rootName.c_str());
		if (isLoop)
		{	//���[�v�����t�Đ����͂�����prevPos������������B
			m_animPosition = MV1GetAttachAnimFrameLocalPosition(m_model, m_currentIndex, frame);
			m_prevPos = m_animPosition;
		}
		m_animPosition = MV1GetAttachAnimFrameLocalPosition(m_model, m_currentIndex, frame);
		m_animVelocity = m_animPosition - m_prevPos;
		m_prevPos = m_animPosition;

	}
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
		m_blend.rate = m_currentAnim == -1 ? 0.0f : 1.0f;//��ԍŏ��̃A�j���[�V�����̓u�����h����0.0f�ɂ���
		m_currentTime = 0.0f;
		m_currentAnim = m_nextAnim;
	}
	if (m_blend.index != -1) {
		if (m_blend.rate > 0.0f) {//�u�����h��
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
}//�u�����h���I��������O�̃A�j���[�V�������f�^�b�`

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

void AnimationComponent::Play(std::string _animName, const float & _speed)
{
	m_nextAnim = m_animList[_animName];
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

VECTOR AnimationComponent::GetAnimVelocity(bool _fixed)
{
	//�w��t���[�����Œ肷�邩
	if (_fixed)
	{
		int frame = MV1SearchFrame(m_model, m_rootName.c_str());
		MV1SetFrameUserLocalMatrix(m_model, frame, MGetIdent());
	}
	return m_animVelocity;
}

void AnimationComponent::GetFrameZeroVector(const std::string & _frameName)
{
	int frame = MV1SearchFrame(m_model, _frameName.c_str());
	MV1SetFrameUserLocalMatrix(m_model, frame, MGetIdent());
}

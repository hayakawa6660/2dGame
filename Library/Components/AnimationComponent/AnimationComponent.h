#pragma once

#include "../ComponentBase.h"

//�A�j���[�V������������͎̂��g�̃N���X�̉��ɂ��̃N���X���p��
//���Ďg��
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
	int		m_nextAnim;		//�ꎞ�I�Ƀ��f���̃n���h����ۊ�
	int		m_currentAnim;	//���Đ����Ă���A�j���[�V�����̃n���h��
	int		m_currentIndex;	//�A�j���[�V����������
	float	m_playSpeed;	//�A�j���[�V�����̃X�s�[�h
	float	m_currentTime;	//���̃A�j���[�V�����̃t���[��	
	float	m_totalTime;	//�A�^�b�`���ꂽ�A�j���[�V�����̑��t���[��
	bool	m_blendFlag;
	bool	m_stop;			//�A�j���[�V�������X�g�b�v���邩�ǂ���
	bool	m_reverse;		//�t�Đ������邩�ǂ���

	struct BLEND_ANIM_INFO {
		int		index;		//�A�j���[�V��������O
		float	rate;		//�u�����h��
		float	speed;
		BLEND_ANIM_INFO() :
			index(-1), rate(0.f), speed(0.2f) {}
	};
	BLEND_ANIM_INFO m_blend;
};
#pragma once

#include "../ComponentBase.h"

#include <unordered_map>

//�A�j���[�V������������͎̂��g�̃N���X�̉��ɂ��̃N���X���p��
//���Ďg��
class AnimationComponent : public ComponentBase
{
public:
	AnimationComponent();
	~AnimationComponent();
private:
	void Start()override {}
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

	void Play(std::string _animName, const float& _speed = 0.5f);
	void SetBlendFlag(bool _flag) { m_blendFlag = _flag; }
	void SetPlaySpeed(const float& _speed);
	void SetBlendSpeed(const float& _speed);
	void Stop(bool _stop) { m_stop = _stop; }
	void SetBody(int _model) { m_model = _model; }
	void SetAnim(std::string _animName, int _handle) { if (!m_animList.count(_animName)) m_animList[_animName] = _handle; }
	void SetReverce(bool _flag) { m_reverse = _flag; }
	//�ړ��ʓ��A�ړ����]�Ɋւ�����
	/// <summary>
	/// ���ݍĐ����Ă���A�j���[�V�����ňړ��������̃��[�J���̃|�W�V�������擾����B
	/// ���[�J���̌��_����̈ړ��ʂȂ̂Œ���
	/// </summary>
	/// <param name="_frameName">�擾�������|�W�V�����̃{�[��(�t���[����)</param>
	VECTOR GetFramePosition(const std::string &_frameName);

	/// <summary>
	/// �A�j���[�V�����̈ړ��ʂ��擾����B
	/// �O��Ă�GetMoveFrame����̍������Ԃ��Ă���(�ړ���)
	/// ���A�����̓A�j���[�V�������[�v���Ɏ����I��0�ɖ߂�̂�
	/// ���_�ɖ߂�l�ȃA�j���[�V�������[�v�ɂ��Ή����Ă���B
	/// �� �ĂԂ��тɍ������X�V�����̂�1�t���[���Ă΂Ȃ������ꍇ�A2�t���[�����̈ړ��ʂ��Ԃ�
	/// </summary>
	/// <param name="_frameName">�擾�������|�W�V�����̃{�[��(�t���[����)</param>
	/// <param name="_fixd">�w��{�[��(�t���[��)�|�W�V������0�ɌŒ肷�邩</param>
	VECTOR GetMoveFrame(const std::string &_frameName, bool _fixed = false);
	/// <summary>
	/// �w��t���[�������[�J���|�W�V����0�ɐݒ肷��B
	/// ���root���Œ肷�邽�߂Ɏg��
	/// </summary>
	/// <param name="_frameName">�擾�������|�W�V�����̃{�[��(�t���[����)</param>
	void GetFrameZeroVector(const std::string &_frameName);
private:
	//�����ŃA�j���[�V�����̃n���h�������̂��n���n�������̂ł�����Ɏ����Ă���
	std::unordered_map<std::string, int> m_animList;
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

	//�ړ��A������
	VECTOR m_prevPos;
};
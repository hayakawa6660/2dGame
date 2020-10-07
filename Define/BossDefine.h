#pragma once

#include <string.h>

namespace BossDefine
{
	//�O���t�B�b�J�[�̓A�j���[�V������ǉ�������
	//���g�ŏ��Ԓʂ�ɐ������݂ő}�����邱��
	//���O�́A�p��ŏ������ƁB
	//�����Ȃ肷���Ȃ��悤�ɒ��ӂ��邱��(�����Ă��R�P��)
	enum class ANIM_STATE
	{
		STAY = 0,			//�ҋ@
		WALK,				//�ړ�
		SCARED,				//����
		ATTACK_1,			//����U��
		ATTACK_2,			//�E��`�F�[���\�[�U�艺�낵
		ATTACK_2_END,		//�E��`�F�[���\�[�I���

		//�A�j���[�V�����s���̂��߁A�ガ�����݂̂��g�����ߐ؂蕪��
		//�q���⋓���������ςɂȂ�̂̓o�����X�����̂��߂����g
		ATTACK_3_START,		//�ːi�U���J�n
		ATTACK_3_LOOP,		//�ːi�U���ړ���
		ATTACK_3_CREAVE,	//�ːi�U���ガ����
		ATTACK_3_END,		//�ːi�U���I���

		ATTACK_4_START,		//�W�����v�U��
		ATTACK_4_LOOP,		//�W�����v��
		ATTACK_4_LANDING,	//���n
		ATTACK_4_END,		//�I�����ҋ@�ȍ~

		BACKJUMP_START,		//�ʏ�W�����v�J�n
		BACKJUMP_LOOP,		//�ʏ�W�����v���[�v
		BACKJUMP_LANDING,	//���n
		BACKJUMP_END,		//�I�����ҋ@�ȍ~

		DEAD,
		MAX,			//�I���B�K����ԍŌ�B�����Ȃ����ƁI
	};
	static constexpr float STAY_TIME = 3.f * 60.f;

	//�����ōU����i�ڂ�������ꏊ�܂ł̋���
	static constexpr float MOVE_RANGE = 800.f;
	//AI�̐؂�ւ��̊
	static constexpr float AI_STAY_RANGE = 800.f;
	static constexpr float AI_JUMP_RANGE = 2000.f;

	//ATTACK_1�̓����蔻��J�n�^�C�~���O
	static constexpr float AT1_COLISION_START = 20.f;
	//ATTACK_1�̓����蔻��I���^�C�~���O
	static constexpr float AT1_COLISION_END = 50.f;

	//ATTACK_2�̓����蔻��J�n�^�C�~���O
	static constexpr float AT2_COLISION_START = 46.f;
	//ATTACK_2�̓����蔻��I���^�C�~���O
	static constexpr float AT2_COLISION_END = 65.f;

	//ATTACK_3�̓����蔻��J�n�^�C�~���O
	static const int AT3_LOOP_TIME = 40;
	static constexpr float AT3_COLISION_START = 13.f;
	//ATTACK_1�̓����蔻��I���^�C�~���O
	static constexpr float AT3_COLISION_END = 18.f;
	//�W�����v�̏���
	static constexpr float JUMP_FIRST_SPEED = 40.f;
}
#pragma once

#include <string>
#include <MyDxLib.h>

/// <summary>
/// �摜�f�[�^�ɕK�v�ȕ��̓����Ă���\����
/// std::string	fileName	= ���f���̓����Ă���t�H���_�̖��O(ResourceManager����̌����ł��g��)
/// int			handle		= �ǂݍ��񂾃��f���̃n���h���i�[�p�ϐ�
struct Model_Info
{
	std::string fileName;
	int handle;
	Model_Info() :
		fileName(""), handle(-1)
	{}
};

/// <summary>
/// �摜�f�[�^�ɕK�v�ȕ��̓����Ă���\����
/// std::string	fileName	= �摜�̓����Ă���t�H���_�̖��O
/// int			handle		= �ǂݍ��񂾉摜�̃n���h���i�[�p�ϐ�
/// int			sizeX		= �摜��X�����T�C�Y
/// int			sizeY		= �摜��Y�����T�C�Y
struct Sprite_Info
{
	std::string fileName;
	int handle;
	int sizeX, sizeY;
};

struct Sound_Info
{
	std::string fileName;
	int handle;
	bool isLoop;
	int volume;
	Sound_Info() :
		fileName(""), handle(-1),
		isLoop(false), volume(255)
	{}
};

struct Time {
	//�l�������ƃI�[�o�[�t���[����0�ɂȂ�̂�double�^
	double deltaTime;	//�O�񎞊Ԃ���̍�	�������ȂƂ���ɓn���̂ŗe�ʍ팸�̂���const�ŎQ�Ɠn��������
	double oldTime;	//�O�̃t���[��
	double nowTime;	//�Q�[���J�n����̎���
};

enum Direction {
	LEFT = 0,
	RIGHT,
};
//�K�[�h�̏��
struct GuardCollision_Info {
	bool isGuard;		//�K�[�h���Ă��邩
	bool isJustGuard;	//�W���X�g�K�[�h�ł�����

	int model;

	VECTOR myPos;
	VECTOR guardPos;	//�K�[�h�̈�ԏ�

	float radius;		//�K�[�h�ƃv���C���[�̔��a
	GuardCollision_Info() :isGuard(false), isJustGuard(false),
		model(-1), myPos{ 0.0f,0.0f,0.0f }, guardPos{ 0.0f,0.0f,0.0f },
		radius(0.0f){}
};

enum HIT_INFO {//�q�b�g�������̏��
	NO_HIT = 0,
	HIT,
	GUARD,
};
//�U�����̃R���C�_�[���
struct Attack_Info {
	VECTOR top;
	VECTOR bottom;
	float radius;
	Attack_Info() :top{ 0,0,0 }, bottom{ 0,0,0 }, radius(0.0f){}
};
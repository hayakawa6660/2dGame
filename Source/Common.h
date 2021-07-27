#pragma once

#include <string>
#include <MyDxLib.h>
#include <functional>

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
/// �摜�f�[�^�̓n���h���[�̏������������ē������`�ł͂Ȃ��̂ŁA������function���܂�ł��܂��B
/// std::string		fileName	= �摜�̓����Ă���t�H���_�̖��O
/// VECTOR			position	= �摜��2D�|�W�V����(Z�͕`�揇�Ɋ֌W���Ă���B�傫����Ύ�O�ɗ���)
/// int				handle		= �ǂݍ��񂾉摜�̃n���h���i�[�p�ϐ�
/// int				sizeX		= �摜��X�����T�C�Y
/// int				sizeY		= �摜��Y�����T�C�Y
/// float			alpha		= �摜�̓����x
/// std::function	function	= �摜��`�悷��֐��B�g������FadeManager���Q�l�ɂ��Ă��������B
struct Sprite_Info
{
	std::string fileName;
	VECTOR position;
	int handle;
	int sizeX, sizeY;
	float alpha;
	Sprite_Info() :
		fileName(""), position(VGet(0, 0, 0)), handle(-1), sizeX(0), sizeY(0), alpha(1.f)
	{}
};

/// �T�E���h�n���ɕK�v�ȏ����܂Ƃ߂��\����
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

/// �e�L�X�g��\�������邽�߂ɕK�v�ȏ��
struct Text_Info
{
	std::string text;
	VECTOR position;
	int color;
};
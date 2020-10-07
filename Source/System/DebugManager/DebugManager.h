#pragma once

#include "../../../Library/GameObject/GameObject.h"

#define DEBUG 1

#if DEBUG
#include <vector>
#include <iostream>
#include <map>

class DebugClasses;

class DebugManager : public GameObject
{
public:
	DebugManager(SceneBase* _scene);
	~DebugManager();

private:
	void Update()override;
	void Draw()override;
private:
	std::map<std::string, bool> m_active;

	bool m_isDebugMode;
	std::list<DebugClasses*> m_debugList;

	int m_menuNum;		//DebucClass��������������
	int m_currentNum;	//���ݑI��ł��郁�j���[

	bool m_allDestroy;
private:
	void SelectUpdate();
	void ResetUpdate();
	void DestroyUpdate();
public:

	void SetActive(std::string &_className, bool _active);
	void Puts(int _x, int _y, std::string _classTag, const char * _format, ...);

	/// <summary>
	/// ���݂܂łɍ�����f�o�b�N�̃N���X��S�ď���
	/// </summary>
	void ListAllClear();

	/// <summary>
	/// ���������O�̗v�f���o�^����Ă���΁A����bool�l��Ԃ�
	/// ������ΕK��false���Ԃ��Ă��āA�v�f�͒ǉ�����Ȃ��̂Œ���
	/// </summary>
	/// <param name="_factorName">�f�o�b�N���j���[�ɂ������O</param>
	bool GetFactorFlag(std::string _factorName);
};


//���f�o�b�N���j���[�̌Ăяo����
//XBox�R���g���[���[�ŁAStart + Select + LB + RB����������������
//�L�[�{�[�h��Ctrl + Alt���������ŊJ���܂�
//�J������́A���ꂼ��㉺�L�[(�{�^��)�Ń��j���[��I�����āA
//�E�L�[(�{�^��)�Ō���A�������܂�
namespace Debug
{
	/// <summary>
	/// ���O���Ńf�o�b�N�̃��j���[�𑀍삷��̂��������ꍇ�̊֐�
	/// </summary>
	/// <param name="_classTag">Active���Z�b�g����f�o�b�N�N���X��</param>
	void SetActive(std::string _className, bool _active);

	/// <summary>
	/// �������l��S�ĕ\������
	/// </summary>
	/// <param name="_x">�\��������������X���W</param>
	/// <param name="_y">�\��������������Y���W</param>
	/// <param name="_classTag">��������f�o�b�N�N���X��</param>
	/// <param name="_format">�t�@�C���̃p�X</param>
	void DebugPrintf(int _x, int _y, std::string _classTag, const char *_format...);

	/// <summary>
	/// ���������O�̗v�f���o�^����Ă���΁A����bool�l��Ԃ�
	/// ������Ηv�f��ǉ����ă`�F�b�N����B
	/// ��x�ڂ̍쐬�i�K�ł͕K��false���Ԃ��Ă���̂Œ���
	/// </summary>
	/// <param name="_factorName">�f�o�b�N���j���[�ɂ������O</param>
	bool GetFactorFlag(std::string _factorName);
	/// <summary>
	/// ���������f�o�b�N���j���[�̃��X�g�����ׂč폜����
	/// ��ɗv�f���𑝂₷�߂��Ȃ����߂ɃV�[���̐؂�ւ����Ɏg��
	/// </summary>
	void ListAllClear();
};
#endif
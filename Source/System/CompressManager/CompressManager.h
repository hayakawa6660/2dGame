#pragma once
#include "Library/GameObject/GameObject.h"
#include <windows.h>
#include <shlobj.h>
#include <unordered_map>
#include <mutex>

/*
****************�g�����A�菇*****************
������������������ ���� ������������������
�Q�[�����ɃI�u�W�F�N�g��ǂݍ��ޏꍇ�A�Ή�����Scene��New�֐��̒���
Zip�𓀂����āA���f�������炩���߃��[�h���鏊�܂ł��Ă����Ă��������B��X�ł���

thread ���g���ăN���X��new
��
zip�𓀂��I���܂�Load�֐���ҋ@������ʏ���
��
Load�֐���ResourceLoad�˗�
��
Resource�̃��[�h���I���܂�Start�֐���ҋ@������ʏ���
��
Start�֐��Ń��\�[�X���Q�b�g����B

�Ƃ����菇�𓥂ނ��ƂɂȂ��ϖʓ|���������ƂɂȂ�܂��B
Update�֐���State����������������܂����A�ǂ݂̂��ʏ��������Ȃ��Ƃ����Ȃ��̂�
�ʓ|�������ł���...
������������������

**********************  �����菇  *************************
�N���X��new����
��
�R���X�g���N�^�ŃW�b�v�𓀈˗����o��
��
Load()�֐� : ���\�[�X�}�l�[�W���[�Ƀ��[�h�˗�
��
Start() : GetHandle���g�p���ă��\�[�X���擾����
*/

class CompressManager : public GameObject
{
public:
	CompressManager(GameObject * _scene);
	~CompressManager();
private:
	//Zip�𓀊֐��{��(�Ăяo����UnCompress)
	bool Unzip(IShellDispatch *_pShellDispatch, WCHAR *_lpszZipPath, WCHAR *_lpszOutPath);
	//Unicode������ϊ��֐�(IShell��Unicode�̂ݑΉ��̂���)
	int CharToWchart(const char * _pSrc, wchar_t *_pDest, const size_t _sDestSize);
public:
	/// <summary>
	/// <para> �t�H���_(�f�B���N�g��)���𓀂���B</para>
	/// </summary>
	/// <param name="_zipPath">�𓀂�����zipFile�̃p�X</param>
	/// <param name="_outPath">�𓀂���zipFile��ۑ�����t�H���_(�f�B���N�g��)��</param>
	bool UnCompress(const char *_zipPath, const char *_outPath);

	/// <summary>
	/// <para>�t�H���_(�f�B���N�g��)���폜����B</para>
	/// <para>���̃v���W�F�N�g�Ő��������t�@�C���͎����I�ɍ폜����܂����A</para>
	/// <para>�u���[�N�|�C���g��NULL�G���[�Ȃǂŋ����I�������ꍇ�͂��̊֐����Ăяo����Ȃ��\��������̂�</para>
	/// <para>�v���O�����������������Zip�������āA���[�h���鏈�������邱�Ƃ𐄏����܂�</para>
	/// <para>������������������������������������������������������������</para>
	/// <para>�v���O�����ō폜���邽�߁A�������A��蒼�����ł��Ȃ��\��������܂��B</para>
	/// <para>�g�p���͂��̃t�@�C�����{���ɏ����Ă������t�H���_�Ȃ̂����m�F�̏�g�p���������B</para>
	/// <para>������������������������������������������������������������</para>
	/// </summary>
	/// <param name="lpPathName">�폜�������t�H���_�̖��O</param>
	bool DeleteDirectory(LPCTSTR _lpPathName);

	bool IsUnZip(std::string _outPath);

	bool IsAllUnZip();
private:
	std::mutex m_mutex;
	char m_currentDirectory[256];
	IShellDispatch *m_pShellDispatch;	//Shell�N���p�\����
	std::unordered_map<std::string, bool> m_outFilePath;	//�I����zip�𓀂����t�@�C���͑S���������߁A�񓚂����ꏊ��ۑ����Ă���
};

#if 0
#include "Library/GameObject/GameObject.h"
#include <stdio.h>

class CompressManager : public GameObject
{
public:
	CompressManager(GameObject * _scene);
	~CompressManager();

public:
	void Compress(const char *_infile, const char *_outfile);
	void UnCompress(const char * _infile, const char * _outfile);
private:

	static const int INBUFSIZ = 1024;	/* ���̓o�b�t�@�T�C�Y�i�C�Ӂj */
	static const int OUTBUFSIZ = 1024;	/* �o�̓o�b�t�@�T�C�Y�i�C�Ӂj */

	char m_inbuf[INBUFSIZ];           /* ���̓o�b�t�@ */
	char m_outbuf[OUTBUFSIZ];         /* �o�̓o�b�t�@ */
};

#endif
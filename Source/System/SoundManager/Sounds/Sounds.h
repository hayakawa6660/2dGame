#pragma once

#include "../../../../Library/GameObject/GameObject.h"
#include "../../../Common.h"
#include <unordered_map>

class Sounds : public GameObject
{
public:
	Sounds(SceneBase * _scene);
	~Sounds();

	void Update()override;
	/// <summary>
	/// �w�肵���T�E���h�̃��[�h���s��
	/// �T�E���h���v���C����ꍇ�́A�����ő�����_path�̖��O���g��
	/// </summary>
	/// <param name="_fileName">�t�@�C���̃p�X</param>
	/// <param name="_path">�Ăяo�����Ɏg�����O</param>
	void Load(std::string _folder, std::string _csv);
	/// <summary>
	/// �^�O�̈�v�����T�E���h���Đ�����
	/// </summary>
	/// <param name="_tag">�炵�����T�E���h�̃t�@�C����</param>
	void SoundPlay(std::string _tag);	//PlaySound��DxLIb�֐��ɂ������̂Ŏg���Ȃ�
	/// <summary>
	/// �^�O�̈�v�����T�E���h���~����
	/// </summary>
	/// <param name="_tag">�炵�����T�E���h�̃t�@�C����</param>
	void StopSound(std::string _tag);
	/// <summary>
	/// �S�ẴT�E���h���~����
	/// </summary>
	void AllStop();

private:
	bool m_isLoadEnd;
	bool m_isScene;
	std::unordered_map<std::string, Sound_Info> m_soundList;
public:
	void CheckScene();
};
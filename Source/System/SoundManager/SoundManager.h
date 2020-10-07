#pragma once

#include "../../../Library/GameObject/GameObject.h"

class Sounds;

class SoundManager : public GameObject
{
public:
	SoundManager(SceneBase * _scene);
	~SoundManager();
private:
	void Update()override;
private:
	std::list<Sounds*> m_soundList;
public:
	//Scene�Ŏg���T�E���h�p�̃N���X�𐶐�����
	//Tag�͑S��SceneSound
	Sounds* CreateSceneSound();
	void DestroySceneSound();

	//Common�AScene�̃T�E���h���ׂĂ��~����
	void AllStop();
};
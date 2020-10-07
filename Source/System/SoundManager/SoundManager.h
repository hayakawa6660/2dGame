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
	//Sceneで使うサウンド用のクラスを生成する
	//Tagは全てSceneSound
	Sounds* CreateSceneSound();
	void DestroySceneSound();

	//Common、Sceneのサウンドすべてを停止する
	void AllStop();
};
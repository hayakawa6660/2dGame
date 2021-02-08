#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "Boot/BootScene.h"
#include "Title/titleScene.h"
//#include "Play/PlayScene.h"

SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TitleScene") {
		return new TitleScene();
	}
	/*
	if (name == "PlayScene") {
		return new PlayScene();
	}
	*/
	MessageBox(NULL, ("���̃V�[���͂���܂���\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}

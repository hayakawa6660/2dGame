#pragma once

#include "../../../Library/SceneManager/SceneBase.h"

class BootScene : public SceneBase {
public:
	BootScene();
	~BootScene();
	void Update() override;
};
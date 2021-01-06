#pragma once

#include "../../../Library/SceneManager/SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
private:
	void Update()override;
	void Draw()override;
};
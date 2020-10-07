#pragma once

#include "../../../Library/SceneManager/SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
private:
	void Update()override;
	void Draw()override;
};
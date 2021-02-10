#pragma once

#include "../PlayStateBase.h"

class PlayGame : public PlayStateBase
{
public:
	PlayGame(SceneBase * _scene);
	~PlayGame();
private:
	void Start()override;
	void Update()override;
	void Draw()override;
};
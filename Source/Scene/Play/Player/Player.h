#pragma once

#include "Library/GameObject/GameObject.h"

class Player : public GameObject
{
public:
	Player(SceneBase * _scene);
	~Player();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	void Draw()override;
};
#pragma once

#include "Library/GameObject/GameObject.h"

class EnemyManager : public GameObject
{
public:
	EnemyManager(SceneBase * _scene);
	~EnemyManager();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	void Draw()override;
};
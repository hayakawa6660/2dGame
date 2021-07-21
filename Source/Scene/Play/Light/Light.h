#pragma once

#include "Library/GameObject/GameObject.h"

class Light : public GameObject
{
public:
	Light(SceneBase * _scene);
	~Light();
private:
	void Load()override;
	void Start()override;
	void Update()override;
};
#pragma once

#include "Library/GameObject/GameObject.h"

class Camera : public GameObject
{
public:
	Camera(SceneBase * _scene);
	~Camera();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	void Draw()override;
};
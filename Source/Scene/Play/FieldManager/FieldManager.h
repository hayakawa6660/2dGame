#pragma once

#include "Library/GameObject/GameObject.h"

class FieldManager : public GameObject
{
public:
	FieldManager(SceneBase * _scene);
	~FieldManager();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	void Draw()override;
};
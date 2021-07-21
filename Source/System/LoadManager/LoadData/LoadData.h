#pragma once

#include "Library/GameObject/GameObject.h"

class LoadData : public GameObject
{
public:
	LoadData(SceneBase * _scene);
	~LoadData();

	void Reset();
private:
	void Start()override;
	void Update()override;
private:
	float m_percentage;
};
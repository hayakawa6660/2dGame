#pragma once

#include "Library/GameObject/GameObject.h"

class Shader;
class RenderManager : public GameObject
{
public:
	RenderManager(SceneBase * _scene);
	~RenderManager();
private:
	void Start()override;
	void Update()override;

	void ShadowSetUp()override;
private:
	Shader * m_shader;
};
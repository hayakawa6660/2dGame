#pragma once

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

class Shader;
class Player : public GameObject
{
public:
	Player(SceneBase * _scene);
	~Player();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	//描画関係
	void ShadowSetUp()override;
	void DrawSetUp()override;
	void Draw()override;

private:
	Model_Info m_model;
	//検索時間削減のコピーポインタ
	Shader * m_shader;
};
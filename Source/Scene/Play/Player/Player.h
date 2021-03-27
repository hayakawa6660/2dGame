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
	//�`��֌W
	void ShadowSetUp()override;
	void DrawSetUp()override;
	void Draw()override;

private:
	Model_Info m_model;
	//�������ԍ팸�̃R�s�[�|�C���^
	Shader * m_shader;
	MATRIX m_matrix;
};
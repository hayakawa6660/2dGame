#pragma once

#include "Library/GameObject/GameObject.h"
//�e�X�g�p
#include "Source/Common.h"
#include "Source/System/RenderManager/Shader/Shader.h"
#include "Library/Components/AnimationComponent/AnimationComponent.h"

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
private:
	Model_Info m_testModel;
	//�������ԍ팸�̃R�s�[�|�C���^
	Shader * m_shader;
	AnimationComponent* m_anim;

	int m_hogeTime;
};
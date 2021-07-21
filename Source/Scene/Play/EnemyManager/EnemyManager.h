#pragma once

#include "Library/GameObject/GameObject.h"
//�e�X�g�p
#include "Source/Common.h"
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
private:
	Model_Info m_testModel;
	//�������ԍ팸�̃R�s�[�|�C���^
	AnimationComponent* m_anim;
	int m_hogeTime;
private:
	void Test(const int _key);
};
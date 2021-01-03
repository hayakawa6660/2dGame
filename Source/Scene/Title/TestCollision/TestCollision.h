#pragma once

#include "Library/GameObject/GameObject.h"

class CollisionComponent;
class TestCollision : public GameObject
{
public:
	TestCollision(SceneBase * _scene);
	~TestCollision();
private:
	void Start()override;
	void Update()override;
	void Draw()override;
	void OnCollision(const Hit_Info &_info)override;

	void Hoge(const Hit_Info & _info);
private:
	CollisionComponent * m_collision;
};
#pragma once

#include "Library/GameObject/GameObject.h"
#include "Library/Components/CollisionComponent/CollisionComponent.h"

class FieldBase : public GameObject
{
public:
	FieldBase(SceneBase * _scene);
	virtual ~FieldBase();
protected:
	virtual void Update()override;
	virtual void Draw()override;
protected:	//Ç±ÇÍà»è„åpè≥ÇµÇ»Ç¢ÇÃÇ≈protected
	CollisionComponent * m_collision;
	float m_left, m_right, m_top, m_bottom;
public:
	void SetStatus(const VECTOR & _pos, float _left, float _right, float _top, float _bottom);
};
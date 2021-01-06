#include "NormalFloor.h"
#include "../FieldManager.h"

NormalFloor::NormalFloor(SceneBase * _scene) :
	FieldBase(_scene)
{
}

NormalFloor::~NormalFloor()
{
}

void NormalFloor::Update()
{
	FieldBase::Update();
	//m_collision->SetSqare(GameObject::GetPosition(), m_left, m_right, m_top, m_bottom);
}

void NormalFloor::Draw()
{
	FieldBase::Draw();
	VECTOR pos = GameObject::GetPosition();
	DrawBox((int)(pos.x - m_left), (int)(pos.y - m_top), (int)(pos.x + m_right), (int)(pos.y + m_bottom), 0xaaff00, true);
}

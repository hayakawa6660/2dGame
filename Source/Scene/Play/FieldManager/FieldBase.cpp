#include "FieldBase.h"
#include "Source/System/DebugManager/DebugManager.h"

FieldBase::FieldBase(SceneBase * _scene) :
	GameObject(_scene)
{
	m_collision = GameObject::AddComponent<CollisionComponent>("CollisionComponent");
}

FieldBase::~FieldBase()
{
	m_collision = nullptr;	//é©ìÆçÌèúÇ≥ÇÍÇÈÇÃÇ≈NULLÇ…Ç∑ÇÈÇæÇØÇ≈Ç¢Ç¢
}

void FieldBase::Update()
{
	GameObject::Update();
#if DEBUG
	VECTOR pos = GameObject::GetPosition();
	std::string str = GameObject::GetTag();
	Debug::DebugPrintf((int)pos.x, (int)pos.y, str, str.c_str());
#endif
}

void FieldBase::Draw()
{
	GameObject::Draw();
}

void FieldBase::SetStatus(const VECTOR & _pos, float _left, float _right, float _top, float _bottom)
{
	GameObject::SetPosition(_pos);
	m_left = _left;
	m_right = _right;
	m_top = _top;
	m_bottom = _bottom;
}
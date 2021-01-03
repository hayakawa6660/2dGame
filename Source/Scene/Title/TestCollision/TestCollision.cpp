#include "TestCollision.h"
#include "Library/Components/CollisionComponent/CollisionComponent.h"

TestCollision::TestCollision(SceneBase * _scene) :
	GameObject(_scene)
{
}

TestCollision::~TestCollision()
{
	m_collision = nullptr;
}

void TestCollision::Start()
{
	m_collision = GameObject::AddComponent<CollisionComponent>("Col");
	m_collision->SetEvent("Test", [&](Hit_Info _info) { Hoge(_info); });
	m_collision->RemoveEvent("Test");
	VECTOR pos = GameObject::GetPosition();

	m_collision->SetSphere(pos, 10.f, "Test");
	GameObject::Update();
}

void TestCollision::Update()
{
	GameObject::Update();
	VECTOR pos = GameObject::GetPosition();
	m_collision->SetSphere(pos, 10.f, "Test");
}

void TestCollision::Draw()
{
	VECTOR pos = GameObject::GetPosition();

	DrawCircle((int)pos.x, (int)pos.y, 10, 0xffffff, true);
}

void TestCollision::OnCollision(const Hit_Info &_info)
{
	std::string str = _info.hitObject->GetTag();
}

void TestCollision::Hoge(const Hit_Info & _info)
{
	int a = 0;
}

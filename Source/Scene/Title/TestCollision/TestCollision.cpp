#include "TestCollision.h"
#include "Library/Components/CollisionComponent/CollisionComponent.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Library/Common/commonObjects.h"
#include "Source/System/ResourceManager/ResourceManager.h"

TestCollision::TestCollision(SceneBase * _scene) :
	GameObject(_scene)
{
	/*
	{
		CompressManager * c = CommonObjects::GetInstance()->FindGameObject<CompressManager>("SceneCompress");
		c->UnCompress("data\\Player.zip", "data\\Player");
	}
	*/
}

TestCollision::~TestCollision()
{
	m_collision = nullptr;
}

void TestCollision::Load()
{
	/*
	{
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		p->ModelLoad("data\\Player\\gensin_syuzinkou_amb.mv1");
	}
	*/
}

void TestCollision::Start()
{
	/*
	{
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		int a = p->GetHandle("data\\Player\\gensin_syuzinkou_amb.mv1");
		a += 0;
	}
	*/
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

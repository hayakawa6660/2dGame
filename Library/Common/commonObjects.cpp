#include "commonObjects.h"

CommonObjects * CommonObjects::GetInstance()
{
	static CommonObjects* inst = nullptr;
	if (inst == nullptr)
		inst = new CommonObjects;
	return inst;
}

void CommonObjects::Start()
{
}

void CommonObjects::Update()
{
	objectManager.Update();
}

void CommonObjects::Draw()
{
	objectManager.Draw();
}

void CommonObjects::Release()
{
	objectManager.DeleteAllGameObject();
}

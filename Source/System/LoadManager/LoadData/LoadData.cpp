#include "LoadData.h"

#include "Library/Common/commonObjects.h"
#include "../../ResourceManager/ResourceManager.h"

//�f�o�b�N�p
#include "../LoadManager.h"

LoadData::LoadData(SceneBase * _scene) :
	GameObject(nullptr),
	m_percentage(0.f)
{
}

LoadData::~LoadData()
{
}

void LoadData::Reset()
{
	m_percentage = 0.f;
}

void LoadData::Start()
{
}

void LoadData::Update()
{
	ResourceManager*system = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SystemResource");
	ResourceManager*scene = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
	if (system == nullptr)
		return;
	if (scene == nullptr)
		return;
	int current = system->GetCurrentSize() + scene->GetCurrentSize();
	int max = system->GetMaxSize() + scene->GetMaxSize();
	m_percentage = (float)current / (float)max * 100.f;
}
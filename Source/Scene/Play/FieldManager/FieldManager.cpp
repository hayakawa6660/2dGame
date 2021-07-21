#include "FieldManager.h"

#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"

#include "Library/Render/RenderManager.h"
#include "Library/Render/Render3D/Shader3D/Shader3D.h"

FieldManager::FieldManager(SceneBase * _scene) :
	GameObject(_scene)
{
	CommonObjects* p = CommonObjects::GetInstance();
	{	//モデルのzip解凍
		CompressManager * c = p->FindGameObject<CompressManager>("CompressManager");
		c->UnCompress("data\\Field.zip", "Field");
	}
}

FieldManager::~FieldManager()
{
}

void FieldManager::Load()
{
	{	//モデルを非同期ロード
		m_ground.fileName = "data\\Resource\\Field\\Ground2_1.mv1";
		m_sky.fileName = "data\\Resource\\Field\\SkyDome.mv1";
		
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		p->ModelLoad(m_ground.fileName);
		p->ModelLoad(m_sky.fileName);
	}
}

void FieldManager::Start()
{
	{	//モデルを取得する
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		m_ground.handle = p->GetHandle(m_ground.fileName);
		m_sky.handle = p->GetHandle(m_sky.fileName);

		//モデルをRenderクラスに登録。
		RenderManager::GetInstance()->AddMV1Model("Ground", m_ground.handle, Shader3D::MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW, Shader3D::MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP);
		RenderManager::GetInstance()->AddMV1Model("Sky", m_sky.handle, Shader3D::MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG, Shader3D::MESH_TYPE::NO_SHADER);

		int a = 0;
	}
}

void FieldManager::Update()
{
}
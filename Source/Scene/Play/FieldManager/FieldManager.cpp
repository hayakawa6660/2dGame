#include "FieldManager.h"

#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Source/System/RenderManager/Shader/Shader.h"

FieldManager::FieldManager(SceneBase * _scene) :
	GameObject(_scene)
{
	CommonObjects* p = CommonObjects::GetInstance();
	m_shader = p->FindGameObject<Shader>("Shader");
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
		int a = 0;
	}
}

void FieldManager::Update()
{
}

void FieldManager::ShadowSetUp()
{
	//頂点シェーダーのみを入れ替えて、他キャラも同じピクセルシェーダーでやるので解除はしない
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_SHADOW_SETUP_NORMALMAP);
	MV1DrawModel(m_ground.handle);

	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG);
	MV1DrawModel(m_sky.handle);
}

void FieldManager::DrawSetUp()
{
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW);
	MV1DrawModel(m_ground.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);
}

void FieldManager::Draw()
{
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_DIFF_SPEC_NORM_SHADOW);
	MV1DrawModel(m_ground.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);

	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_NO_LIGHTING_DIFFONLY_FOG);
	MV1DrawModel(m_sky.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);
}

#include "EnemyManager.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"

EnemyManager::EnemyManager(SceneBase * _scene) :
	GameObject(_scene)
{
	CommonObjects* p = CommonObjects::GetInstance();
	m_shader = p->FindGameObject<Shader>("Shader");

	m_anim = GameObject::AddComponent<AnimationComponent>("TestAnim");
	/*
	{
		CompressManager * c = CommonObjects::GetInstance()->FindGameObject<CompressManager>("SceneCompress");
		c->UnCompress("data\\Player.zip", "data\\Player");
	}
	*/
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Load()
{
	{
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		/*
		m_testModel.fileName = "data\\Test\\player_model.mv1";
		p->ModelLoad(m_testModel.fileName);
		p->ModelLoad("data\\Test\\player_001.mv1");
		*/
		m_testModel.fileName = "data\\Test\\PC.mv1";
		p->ModelLoad(m_testModel.fileName);
		p->ModelLoad("data\\Test\\Anim_Run.mv1");
	}
}

void EnemyManager::Start()
{
	ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
	m_testModel.handle = MV1DuplicateModel(p->GetHandle(m_testModel.fileName));
	m_anim->SetBody(m_testModel.handle);
	/*
	m_anim->SetAnim("Run", p->GetHandle("data\\Test\\player_001.mv1"));
	m_anim->SetBlendFlag(true);
	m_anim->Play("Run");
	*/
	m_anim->SetAnim("Run", p->GetHandle("data\\Test\\Anim_Run.mv1"));
	m_anim->SetBlendFlag(true);
	m_anim->Play("Run");

}

void EnemyManager::Update()
{
	GameObject::Update();
}

void EnemyManager::Draw()
{
	MV1SetScale(m_testModel.handle, VGet(0.01, 0.01, 0.01));
	MV1SetPosition(m_testModel.handle, VGet(0, 0, 3));
	static float rotY = 0.f;
	rotY += 0.03f;
	MV1SetRotationXYZ(m_testModel.handle, VGet(0, rotY, 0));

	int triListNum = MV1GetTriangleListNum(m_testModel.handle);
	for (int i = 0; i < triListNum; i++)
	{
		//4ボーン以内か5ボーン以上でシェーダーを分ける
		int type = MV1GetTriangleListVertexType(m_testModel.handle, i);
		if (type == DX_MV1_VERTEX_TYPE_4FRAME)
			m_shader->SetMeshTypeShader(Shader::MESH_TYPE::SKIN4_DIFFUSE_ONLY);
		else if (type == DX_MV1_VERTEX_TYPE_8FRAME)
			m_shader->SetMeshTypeShader(Shader::MESH_TYPE::SKIN8_DIFFUSE_ONLY);

		MV1DrawTriangleList(m_testModel.handle, i);
	}
}

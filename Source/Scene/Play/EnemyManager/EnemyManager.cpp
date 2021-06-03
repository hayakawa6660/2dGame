#include "EnemyManager.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"

EnemyManager::EnemyManager(SceneBase * _scene) :
	GameObject(_scene),
	m_hogeTime(120)
{
	CommonObjects* p = CommonObjects::GetInstance();
	m_shader = p->FindGameObject<Shader>("Shader");

	m_anim = GameObject::AddComponent<AnimationComponent>("TestAnim");
	GameObject::SetScale(VGet(0.01, 0.01, 0.01));
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
	m_anim->SetAnim("Run", p->GetHandle("data\\Test\\Anim_Run.mv1"));
	//m_anim->SetBlendFlag(true);
	m_anim->Play("Run", 0.5f);
	m_anim->SetReverce(true);
	m_anim->SetRootName("root");
}

void EnemyManager::Update()
{
	GameObject::Update();

	if (--m_hogeTime <= 0)
	{
		m_hogeTime = GetRand(120) + 60;
		//m_anim->SetPlaySpeed(GetRand(10) * 0.1);
	}
	VECTOR rot = GameObject::GetRotation();
	rot.y += 0.03f;
	VECTOR velocity = m_anim->GetAnimVelocity("root", true);
	MATRIX mScl = MGetScale(GameObject::GetScale());
	MATRIX mRotY = mScl * MGetRotY(rot.y);
	VECTOR v = VTransform(velocity, mRotY);
	//ローカルは軸が逆なので-=
	VECTOR pos = GameObject::GetPosition();
	pos += v;
	pos.y = 0.f;
	GameObject::SetRotation(rot);
	GameObject::SetPosition(pos);
}

void EnemyManager::Draw()
{
	MATRIX mScl = MGetScale(VGet(0.01, 0.01, 0.01));
	MATRIX mr = mScl * MGetRotY(GameObject::GetRotation().y);
	MATRIX mt = MGetTranslate(GameObject::GetPosition());
	MATRIX m = MMult(mr, mt);
	MV1SetMatrix(m_testModel.handle, m);



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

#include "Player.h"

#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Source/System/RenderManager/Shader/Shader.h"

Player::Player(SceneBase * _scene) :
	GameObject(_scene)
{
	CommonObjects* p = CommonObjects::GetInstance();
	m_shader = p->FindGameObject<Shader>("Shader");
	{	//モデルのzip解凍
		CompressManager * c = p->FindGameObject<CompressManager>("SceneCompress");
		c->UnCompress("data\\Player.zip", "data\\Player");
	}
}

Player::~Player()
{
}

void Player::Load()
{
	{	//モデルを非同期ロード
		m_model.fileName = "data\\Player\\gensin_syuzinkou_amb.mv1";
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		p->ModelLoad(m_model.fileName);
	}
}

void Player::Start()
{
	{	//モデルを取得する
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		m_model.handle = p->GetHandle(m_model.fileName);
	}
}

void Player::Update()
{
}

void Player::ShadowSetUp()
{
	MV1SetPosition(m_model.handle, VGet(0, 0, 0));
}

void Player::DrawSetUp()
{
	MV1SetPosition(m_model.handle, VGet(0, 0, 0));
}

void Player::Draw()
{
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_DIFF_SPEC_TOON);
	MV1DrawModel(m_model.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);
}

#include "Player.h"

#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Source/System/RenderManager/Shader/Shader.h"

Player::Player(SceneBase * _scene) :
	GameObject(_scene),
	m_matrix(MGetIdent()),
	m_position()
{
	CommonObjects* p = CommonObjects::GetInstance();
	m_shader = p->FindGameObject<Shader>("Shader");
	{	//モデルのzip解凍
		CompressManager * c = p->FindGameObject<CompressManager>("CompressManager");
		c->UnCompress("data\\Player.zip", "Player");
	}
	ChangeState<PlayerWaitState>();
	
}

Player::~Player()
{
	if (m_state) {
		delete m_state;
		m_state = nullptr;
	}
}

void Player::Load()
{
	{	//モデルを非同期ロード
		m_model.fileName = "data\\Resource\\Player\\gensin_syuzinkou_amb.mv1";
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
	m_movement.MovementUpdate(&m_matrix);
	m_position = VGet(m_matrix.m[3][0], m_matrix.m[3][1], m_matrix.m[3][2]);
	SetPosition(m_position);
	if (m_state) {
		m_state->Update();
	}
}

void Player::ShadowSetUp()
{
	MV1SetPosition(m_model.handle, VGet(0, 0, 0));
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMALMAP);
	MV1DrawModel(m_model.handle);
}

void Player::DrawSetUp()
{
	MV1SetPosition(m_model.handle, VGet(0, 0, 0));
}

void Player::Draw()
{
	MV1SetMatrix(m_model.handle, m_matrix);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NMESH_DIFF_SPEC_TOON);
	MV1DrawModel(m_model.handle);
	m_shader->SetMeshTypeShader(Shader::MESH_TYPE::NO_SHADER);
}

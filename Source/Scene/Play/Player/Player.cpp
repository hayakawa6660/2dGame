#include "Player.h"

#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
//�����Render�ǉ�����
#include "Library/Render/RenderManager.h"
#include "Library/Render/Render3D/Shader3D/Shader3D.h"

Player::Player(SceneBase * _scene) :
	GameObject(_scene),
	m_matrix(MGetIdent()),
	m_position()
{
	CommonObjects* p = CommonObjects::GetInstance();
	{	//���f����zip��
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
	{	//���f����񓯊����[�h
		m_model.fileName = "data\\Resource\\Player\\gensin_syuzinkou_amb.mv1";
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		p->ModelLoad(m_model.fileName);
	}
}

void Player::Start()
{
	{	//���f�����擾����
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		m_model.handle = p->GetHandle(m_model.fileName);
		//���f����Render�N���X�ɓo�^�B
		RenderManager::GetInstance()->AddMV1Model("Player", m_model.handle, Shader3D::MESH_TYPE::NMESH_DIFF_SPEC_TOON, Shader3D::MESH_TYPE::NMESH_SHADOW_SETUP_NOT_NORMAL);
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

	//�`����@���ς�����̂ň�UPlayer���؂�ď����܂��B
}
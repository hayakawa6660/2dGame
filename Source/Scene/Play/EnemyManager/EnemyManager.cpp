#include "EnemyManager.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Source/System/InputManager/InputManager.h"

#include "Library/Render/RenderManager.h"

//#include "Source/System/KeyboardManager/KeyboardManager.h"

EnemyManager::EnemyManager(SceneBase * _scene) :
	GameObject(_scene),
	m_hogeTime(120)
{
	CommonObjects* p = CommonObjects::GetInstance();

	m_anim = GameObject::AddComponent<AnimationComponent>("TestAnim");
	GameObject::SetScale(VGet(0.01, 0.01, 0.01));
	InputManager * key = p->FindGameObject<InputManager>("InputManager");
	//key->AddKeyBind("Hoge", KEY_INPUT_LSHIFT);
	//key->AddFunction("Hoge", [this](const int _key) { Test(_key); });
	//������������
	key->AddKeyBindFunction("Hoge", KEY_INPUT_LSHIFT, [this](const int _key) { Test(_key); });

	//�L�[�ǉ��`�F�b�N
	key->AddKey("Hoge", KEY_INPUT_LCONTROL);

}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Load()
{
	{
		ResourceManager* p = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
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
	m_anim->SetBlendFlag(true);
	m_anim->Play("Run", 0.1f);
	//�t�Đ��ړ��m�F�p
	m_anim->SetReverce(false);
	//������Z�b�g����ƈړ��ʂ��擾�ł���悤�ɂȂ�B
	m_anim->SetRootName("root");

	RenderManager::GetInstance()->AddMV1Model("Enemy", m_testModel.handle, Shader3D::MESH_TYPE::SKIN8_SHADOW_SETUP_NOT_NORMAL, Shader3D::MESH_TYPE::SKIN4_DIFF_SPEC_NORM, false, true);
}

void EnemyManager::Update()
{
	GameObject::Update();

	{
		CommonObjects* p = CommonObjects::GetInstance();
		InputManager * key = p->FindGameObject<InputManager>("InputManager");
		//�������P�̂ł��g���܂��B
		if (key->IsInput("Hoge"))
			int a = 0;
		if (key->IsTrigger("Hoge"))
			int a = 0;
	}

	if (--m_hogeTime <= 0)
	{
		m_hogeTime = GetRand(120) + 60;
		//�X�s�[�h�ύX�m�F�p
		m_anim->SetPlaySpeed(GetRand(10) * 0.1);
	}
	//��]�m�F�p
	VECTOR rot = GameObject::GetRotation();
	rot.y += 0.03f;
	VECTOR velocity = m_anim->GetAnimVelocity(true);
	//�ړ��ʂ����̑傫���Ȃ̂ŁA���݂̑傫���ɍ��킹��B
	MATRIX mScl = MGetScale(GameObject::GetScale());
	MATRIX mRotY = mScl * MGetRotY(rot.y);
	VECTOR newVelocity = VTransform(velocity, mRotY);
	//���[�J���͎����t�Ȃ̂�-=
	VECTOR pos = GameObject::GetPosition();
	pos += newVelocity;
	pos.y = 0.f;
	GameObject::SetRotation(rot);
	GameObject::SetPosition(pos);

	//Draw�������Ȃ����̂ŁAUpdate��SetMatrix()��ASetPosition()�܂ŏ���
	//Scl * mRotY�����ɂ���̂ł��łɂ�����g��
	MATRIX mTrans = mRotY * MGetTranslate(GameObject::GetPosition());
	MV1SetMatrix(m_testModel.handle, mTrans);
}


void EnemyManager::Test(const int _key)
{
	int a = 0;
}

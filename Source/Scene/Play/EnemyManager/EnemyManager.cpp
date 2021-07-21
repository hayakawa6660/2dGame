#include "EnemyManager.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/CompressManager/CompressManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"
#include "Source/System/InputManager/InputManager.h"

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
	//↑かもしくは
	key->AddKeyBindFunction("Hoge", KEY_INPUT_LSHIFT, [this](const int _key) { Test(_key); });

	//キー追加チェック
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
	//逆再生移動確認用
	//m_anim->SetReverce(true);
	//これをセットすると移動量が取得できるようになる。
	m_anim->SetRootName("root");
}

void EnemyManager::Update()
{
	GameObject::Update();

	{
		CommonObjects* p = CommonObjects::GetInstance();
		InputManager * key = p->FindGameObject<InputManager>("InputManager");
		//もちろん単体でも使えます。
		if (key->IsInput("Hoge"))
			int a = 0;
		if (key->IsTrigger("Hoge"))
			int a = 0;
	}

	if (--m_hogeTime <= 0)
	{
		m_hogeTime = GetRand(120) + 60;
		//スピード変更確認用
		m_anim->SetPlaySpeed(GetRand(10) * 0.1);
	}
	//回転確認用
	VECTOR rot = GameObject::GetRotation();
	rot.y += 0.03f;
	VECTOR velocity = m_anim->GetAnimVelocity(true);
	//移動量が元の大きさなので、現在の大きさに合わせる。
	MATRIX mScl = MGetScale(GameObject::GetScale());
	MATRIX mRotY = mScl * MGetRotY(rot.y);
	VECTOR v = VTransform(velocity, mRotY);
	//ローカルは軸が逆なので-=
	VECTOR pos = GameObject::GetPosition();
	pos -= v;
	pos.y = 0.f;
	GameObject::SetRotation(rot);
	GameObject::SetPosition(pos);
}


void EnemyManager::Test(const int _key)
{
	int a = 0;
}

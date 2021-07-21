#include "PlayLoad.h"
//Parent or Child
#include "../../PlayScene.h"
#include "../PlayGame/PlayGame.h"
//Scene
#include "../../EnemyManager/EnemyManager.h"
#include "../../Player/Player.h"
#include "../../FieldManager/FieldManager.h"
#include "../../Light/Light.h"
#include "Library/Common/commonObjects.h"
#include "Source/System/ThreadManager/ThreadManager.h"
#include "Source/System/ResourceManager/ResourceManager.h"

/*
Player
FieldManager
	FieldBase
	FieldObject
Camera
Light
*/

PlayLoad::PlayLoad(SceneBase * _scene) :
	PlayStateBase(_scene),
	m_state(STATE::UNZIP),
	m_canNext(false)
{
	ThreadManager * th = CommonObjects::GetInstance()->FindGameObject<ThreadManager>("ThreadManager");
	th->CreateThread<void>([this] { Load(); });
}

PlayLoad::~PlayLoad()
{
}

void PlayLoad::Load()
{
	SceneBase * p = GameObject::GetScene();
	p->CreateGameObject<EnemyManager>("EnemyManager");
	p->CreateGameObject<Player>("Player");
	p->CreateGameObject<FieldManager>("FieldManager");
	p->CreateGameObject<Light>("Light");

	//�X���b�h�I����`����
	ThreadManager * th = CommonObjects::GetInstance()->FindGameObject<ThreadManager>("ThreadManager");
	th->EndThread();
	m_canNext = true;
}

void PlayLoad::Start()
{
}

void PlayLoad::Update()
{
	switch (m_state)
	{
	case STATE::UNZIP:
	{
		if (m_canNext)
		{	//�S�Đ�������Ă����玟�̃X�e�[�g��
			m_canNext = false;
			m_state = STATE::LOAD;
			PlayScene * p = dynamic_cast<PlayScene*>(GameObject::GetScene());
			p->GameObjectUpdate();	//�I�u�W�F�N�g��Updata��1�t���[���񂵁ALoad�֐��ɓ����
		}
	}
	break;
	case STATE::LOAD:
	{
		ResourceManager * rsc = CommonObjects::GetInstance()->FindGameObject<ResourceManager>("SceneResource");
		if (rsc->AllLoadEndCheck())
		{
			PlayScene * p = dynamic_cast<PlayScene*>(GameObject::GetScene());
			p->SetNextState<PlayGame>("PlayGame");		//�I�u�W�F�N�g��Updata��1�t���[���񂵁ALoad�֐��ɓ����
		}
	}
	break;
	default:	break;
	}
}
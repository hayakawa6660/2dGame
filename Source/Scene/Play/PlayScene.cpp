#include "PlayScene.h"
//#include "PlayState/PlayNewClasses/PlayNewClasses.h"
#include "PlayState/PlayLoad/PlayLoad.h"
#include "Camera/Camera.h"
#include "Library/Common/commonObjects.h"
#include "Source/System/RenderManager/Shader/Shader.h"

PlayScene::PlayScene() :
	m_next(nullptr),
	m_current(nullptr)
{
	SetNextState<PlayLoad>("PlayLoad");

	SetFogEnable(TRUE);
	// フォグの色を白色にする
	SetFogColor(150, 150, 255);
	//SetFogColor(255, 50, 50);

	// フォグの開始距離を0、終了距離を1500にする
	SetFogStartEnd(0.0f, 1500.f);

}

PlayScene::~PlayScene()
{
}

void PlayScene::Load()
{
}

void PlayScene::ChangeState()
{
	if (!m_next) return;
	if (m_current) delete m_current;
	m_current = m_next;
	m_current->Start();
	m_next = nullptr;
}

void PlayScene::GameObjectUpdate()
{
	SceneBase::Update();
}

void PlayScene::Update()
{
	ChangeState();
	if (m_current)
		m_current->Update();

	if (m_current->GetTag() != "PlayLoad")
	{
		SceneBase::Update();
	}
}

void PlayScene::Draw()
{
	if (m_current)
		m_current->Draw();
	Camera *camera = SceneBase::FindGameObject<Camera>("Camera");
	if (m_current->GetTag() != "PlayLoad")
	{
		Shader*shader = CommonObjects::GetInstance()->FindGameObject<Shader>("Shader");
		{
			shader->SetShadowSetUpShader(true);
			SceneBase::ShadowSetUp();
			shader->SetShadowSetUpShader(false);
		}
		int num = shader->GetMirrorNum();
		{	//鏡(水面)から見た時の反射板のセットアップ
			VECTOR pos = camera->GetPosition();
			VECTOR target = camera->GetTarget();
			for (int i = 0; i < num; ++i)
			{
				shader->SetUpMirror(i, pos, target);
				SceneBase::DrawSetUp();
			}
		}
		{	//本表示
			camera->SetCameraPosAndDir();
			SceneBase::Draw();
		}
		{	//水面表示
			for (int i = 0; i < num; ++i)
				shader->MirrorRender(i);
		}
	}

}

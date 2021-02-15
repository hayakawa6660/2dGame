#include "Camera.h"
//Scene
#include "../PlayScene.h"
#include "../Player/Player.h"
//System
#include "Library/Common/commonObjects.h"
#include "Source/System/RenderManager/Shader/Shader.h"
#include "Source/System/ControllerManager/ControllerManager.h"
#include "Source/System/CacheManager/CacheManager.h"
#include "Source/System/RenderManager/Shader/Shader.h"

Camera::Camera(SceneBase * _scene) :
	GameObject(_scene),
	m_target(VGet(0, 15, 0)),
	m_offset(VGet(0, 0.3f, -2.5f)),
	m_checkOff(VGet(0, 0.3f, -5.f))
{
	m_controller = CommonObjects::GetInstance()->FindGameObject<ControllerManager>("ControllerManager");
}

Camera::~Camera()
{
}

void Camera::Start()
{
	//RotateUpdate
	VECTOR rot = GameObject::GetRotation();
	RotateUpdate(rot);
	//TarugetUpdate
	m_target = GameObject::GetScene()->FindGameObject<Player>("Player")->GetPosition();
	m_target.y += 1.f;
	//CameraMein
	MATRIX mRot = MGetRotX(rot.x) * MGetRotY(rot.y);
	VECTOR offset = VTransform(m_offset, mRot);
	VECTOR pos = m_target + offset;
	GameObject::SetPosition(pos);
	GameObject::SetRotation(rot);

	//Updateで画面に入っているかどうか確認するため
	//本来映るところより少し後ろにカメラを置いておく
	VECTOR check = VTransform(m_checkOff, mRot);
	m_checkPos = m_target + check;
	SetCameraPositionAndTarget_UpVecY(m_checkPos, m_target);
}

void Camera::Update()
{
	//RotateUpdate
	VECTOR rot = GameObject::GetRotation();
	RotateUpdate(rot);
	//TarugetUpdate
	m_target = GameObject::GetScene()->FindGameObject<Player>("Player")->GetPosition();
	m_target.y += 1.f;
	CommonObjects::GetInstance()->FindGameObject<Shader>("Shader")
		->SetTargetPosition(m_target);
	//CameraMein
	MATRIX mRot = MGetRotX(rot.x) * MGetRotY(rot.y);
	VECTOR offset = VTransform(m_offset, mRot);
	VECTOR pos = m_target + offset;

	GameObject::SetPosition(pos);
	GameObject::SetRotation(rot);

	//Updateで画面に入っているかどうか確認するため
	//本来映るところより少し後ろにカメラを置いておく
	VECTOR check = VTransform(m_checkOff, mRot);
	m_checkPos = m_target + check;
	SetCameraPositionAndTarget_UpVecY(m_checkPos, m_target);
}

void Camera::RotateUpdate(VECTOR &_rot)
{
	if (m_controller->GetKeyInput(InputComponent::KEY_ID::RIGHT))
	{
		_rot.y += 0.1f;
	}
	else if (m_controller->GetKeyInput(InputComponent::KEY_ID::LEFT))
	{
		_rot.y -= 0.1f;
	}

	VECTOR stick = m_controller->GetRStick_XY();
	if (stick.x + stick.y == 0.f)
		return;
	stick.x /= 5000.f;
	stick.y /= 5000.f;
	_rot.x -= stick.y;
	_rot.y += stick.x;

	if (_rot.x >= 1.f)
		_rot.x = 1.f;
	else if (_rot.x <= -1.f)
		_rot.x = -1.f;
}

void Camera::SetCameraPosAndDir()
{
	// 裏画面を描画対象にする
	SetDrawScreen(DX_SCREEN_BACK);
	// 画面をクリア
	ClearDrawScreen();

	SetCameraNearFar(0.1f, 3000.0f);

	VECTOR pos = GameObject::GetPosition();

	SetCameraPositionAndTarget_UpVecY(pos, m_target);
}

bool Camera::IsInCamera(const VECTOR & _pos)
{
	SetCameraNearFar(0.01f, 100.f);
	return (!CheckCameraViewClip(_pos));
}

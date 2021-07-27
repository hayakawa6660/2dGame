#include "Camera.h"

#include "Library/Common/commonObjects.h"
#include "Source/System/InputManager/InputManager.h"
/*
//Scene
#include "../PlayScene.h"
#include "../Player/Player.h"
//System
#include "Source/System/RenderManager/Shader/Shader.h"
#include "Source/System/CacheManager/CacheManager.h"
#include "Source/System/RenderManager/Shader/Shader.h"
*/
Camera::Camera() :
	m_target(VGet(0, 1.f, 0)),
	m_position(VGet(0, 0, 0)),
	m_rotation(VGet(0, 0, 0)),
	m_offset(VGet(0, 0.3f, -2.5f)),
	m_checkOff(VGet(0, 0.3f, -5.f))
{
	m_input = CommonObjects::GetInstance()->FindGameObject<InputManager>("InputManager");
	//RotateUpdate
	RotateUpdate(m_rotation);
	//TarugetUpdate
	//m_target = GameObject::GetScene()->FindGameObject<Player>("Player")->GetPosition();
	//m_target.y += 1.f;
	//CameraMein
	MATRIX mRot = MGetRotX(m_rotation.x) * MGetRotY(m_rotation.y);
	VECTOR offset = VTransform(m_offset, mRot);
	VECTOR pos = m_target + offset;
	m_position = pos;

	//Updateで画面に入っているかどうか確認するため
	//本来映るところより少し後ろにカメラを置いておく
	VECTOR check = VTransform(m_checkOff, mRot);
	m_checkPos = m_target + check;
	SetCameraPositionAndTarget_UpVecY(m_checkPos, m_target);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//RotateUpdate
	//VECTOR rot = GameObject::GetRotation();
	RotateUpdate(m_rotation);

	//CameraMein
	MATRIX mRot = MGetRotX(m_rotation.x) * MGetRotY(m_rotation.y);
	VECTOR offset = VTransform(m_offset, mRot);
	VECTOR pos = m_target + offset;
	m_position = pos;

	//Updateで画面に入っているかどうか確認するため
	//本来映るところより少し後ろにカメラを置いておく
	VECTOR check = VTransform(m_checkOff, mRot);
	m_checkPos = m_target + check;
	SetCameraPositionAndTarget_UpVecY(m_checkPos, m_target);
}

void Camera::RotateUpdate(VECTOR &_rot)
{
	if (m_input->IsInput("RIGHT"))
	{
		_rot.y += 0.1f;
	}
	else if (m_input->IsInput("LEFT"))
	{
		_rot.y -= 0.1f;
	}
	/*
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
		*/
}

void Camera::SetCameraPosAndDir()
{
	// 裏画面を描画対象にする
	SetDrawScreen(DX_SCREEN_BACK);
	// 画面をクリア
	ClearDrawScreen();

	SetCameraNearFar(0.1f, 3000.0f);

	//VECTOR pos = GameObject::GetPosition();

	SetCameraPositionAndTarget_UpVecY(m_position, m_target);
}

bool Camera::IsInCamera(const VECTOR & _pos)
{
	SetCameraNearFar(0.01f, 100.f);
	return (!CheckCameraViewClip(_pos));
}

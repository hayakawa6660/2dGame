#include "CameraComponent.h"

CameraComponent::CameraComponent() :
	m_offset(VGet(0, 3, 3)),
	m_target(VGet(0, 0, 0))
{
	SetPerspective(DX_PI_F / 2.f);
	SetCameraNearFar(0.1f, 1000.f);
	MATRIX mrot = MGetRotY(0.f);
	VECTOR offset = VTransform(m_offset, mrot);
	VECTOR position = m_target + offset;
	SetCameraPositionAndTarget_UpVecY(position, m_target);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::SetPerspective(float _fov)
{
	SetupCamera_Perspective(_fov);
}

void CameraComponent::SetOrtho(float _size)
{
	SetupCamera_Ortho(_size);
}

void CameraComponent::PositionAndTargetUpdate(const VECTOR & _rotation)
{
	MATRIX mrot = MGetRotY(_rotation.y) * MGetRotZ(_rotation.z) * MGetRotX(_rotation.x);
	VECTOR offset = VTransform(m_offset, mrot);
	VECTOR position = m_target + offset;
	SetCameraPositionAndTarget_UpVecY(position, m_target);
}

void CameraComponent::SetPositionAndTarget(const VECTOR & _position, const VECTOR & _target)
{
	SetCameraPositionAndTarget_UpVecY(_position, _target);
}

bool CameraComponent::CheckCameraViewClip(const VECTOR & _p1, const VECTOR & _p2)
{
	if (CheckCameraViewClip_Box(_p1, _p2))
		return true;
	return false;
}

void CameraComponent::SetNearFar(float _near, float _far)
{
	if (_near <= 0.f)	//0以下だと表示範囲がバグるので、補正する
		_near = 0.1f;
	SetCameraNearFar(_near, _far);
}

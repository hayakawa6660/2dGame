#pragma once

#include "Library/GameObject/GameObject.h"

class ControllerManager;
class Camera : public GameObject
{
public:
	Camera(SceneBase *_scene);
	~Camera();
private:
	void Start()override;
	void Update()override;

	void RotateUpdate(VECTOR &_rot);
public:
	void SetCameraPosAndDir();
private:
	VECTOR m_target;
	VECTOR m_offset;
	VECTOR m_checkOff;
	VECTOR m_checkPos;
	ControllerManager *m_controller;
public:
	const VECTOR &GetTarget() { return m_target; }
	bool IsInCamera(const VECTOR &_pos);
};
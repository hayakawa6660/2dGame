#pragma once

#include "Library/GameObject/GameObject.h"

class InputManager;
class Camera
{
public:
	Camera();
	~Camera();
	void Update();
private:
	void RotateUpdate(VECTOR &_rot);
public:
	void SetCameraPosAndDir();
private:
	VECTOR m_position;
	VECTOR m_rotation;
	VECTOR m_target;
	VECTOR m_offset;
	VECTOR m_checkOff;
	VECTOR m_checkPos;
	InputManager *m_input;
public:
	bool IsInCamera(const VECTOR &_pos);

	const VECTOR &GetTarget()	{ return m_target; }
	const VECTOR &GetPosition() { return m_position; }
	const VECTOR &GetRotation() { return m_rotation; }
	const VECTOR &GetOffset()	{ return m_offset; }

	void SetTarget(const VECTOR & _target)	{ m_target = _target; }
	void SetPosition(const VECTOR & _pos)	{ m_position = _pos; }
	void SetRotation(const VECTOR & _rot)	{ m_rotation = _rot; }
	void SetOffset(const VECTOR &_off)		{ m_offset = _off; }
};
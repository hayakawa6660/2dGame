#pragma once
#include <MyDxlib.h>

//class ControllerManager;
class PlayerMovement {
public:
	PlayerMovement();
	~PlayerMovement();
	void MovementUpdate(MATRIX* _matrix);
	void SetMovemetSpeed(float _movementSpeed);
private:

	void VelocityUpdate();
	/// <summary>
	/// �f�o�b�O�p
	/// </summary>
	/// <returns></returns>
	void MoveToKeyAngleUpdate();
	
	float m_movementSpeed;
	float m_movementMaxSpeed;
	float m_movementAxis;
	float m_rotateSpeed;
	VECTOR velocity;
	MATRIX* matrix;
	//ControllerManager* m_input;
};
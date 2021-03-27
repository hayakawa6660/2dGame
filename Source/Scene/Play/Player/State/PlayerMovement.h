#pragma once
#include <MyDxlib.h>

class InputComponent;
class PlayerMovement {
public:
	PlayerMovement();
	~PlayerMovement();
	void UpdateMove(MATRIX* matrix);
private:
	float GetMoveToKeyAngle();
	
	float m_moveAxis;
	float m_rotateSpeed;
	InputComponent* m_input;
};
#pragma once

#include "../ComponentBase.h"
class AxisComponent : public ComponentBase
{
public:		//Constructor
	AxisComponent();
	~AxisComponent();
private:	//Private Functions
	void Draw()override;
public:		//Public Functions
	void SetAxis(int _maxPos, int _width);
private:	//Variables
	int m_maxPosition;
	int m_width;
};
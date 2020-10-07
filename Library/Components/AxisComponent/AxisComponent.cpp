#include "AxisComponent.h"

AxisComponent::AxisComponent() :
	m_maxPosition(1000),
	m_width(10)
{
}

AxisComponent::~AxisComponent()
{
}

void AxisComponent::Draw()
{
	for (int i = -m_maxPosition; i <= m_maxPosition; i += m_width)
	{
		DrawLine3D(VGet(-10000.f, 0, (float)i), VGet(10000.f, 0.f, (float)i), GetColor(100, 100, 100));
		DrawLine3D(VGet((float)i, 0, -10000.f), VGet((float)i, 0.f, 10000.f), GetColor(100, 100, 100));
	}
	DrawLine3D(VGet(-10000.f, -0.000f, -0.000f), VGet(10000.f, 0.000f, 0.000f), GetColor(255, 0, 0));
	DrawLine3D(VGet(-0.000f, -10000.f, -0.000f), VGet(0.000f, 10000.f, 0.000f), GetColor(0, 255, 0));
	DrawLine3D(VGet(-0.000f, -0.000f, -10000.f), VGet(0.000f, 0.000f, 10000.f), GetColor(0, 0, 255));

}

void AxisComponent::SetAxis(int _maxPos, int _width)
{
	m_maxPosition = _maxPos;
	m_width = _width;
}

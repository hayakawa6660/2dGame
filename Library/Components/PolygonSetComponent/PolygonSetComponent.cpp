#include "PolygonSetComponent.h"
#include <array>

PolygonSetComponent::PolygonSetComponent()
{
	m_sqare.clear();
}

PolygonSetComponent::~PolygonSetComponent()
{
	m_sqare.clear();
}

void PolygonSetComponent::SqareSet(VECTOR & _pos, float _radiusX, float _radiusY)
{
	std::array<VECTOR, 4> polyPos;
	polyPos[0] = VGet(-_pos.x - _radiusX, _pos.y,  _pos.z + _radiusY);
	polyPos[1] = VGet( _pos.x + _radiusX, _pos.y,  _pos.z + _radiusY);
	polyPos[2] = VGet(-_pos.x - _radiusX, _pos.y, -_pos.z - _radiusY);
	polyPos[3] = VGet( _pos.x + _radiusX, _pos.y, -_pos.z - _radiusY);
	m_sqare.emplace_back(polyPos);
}

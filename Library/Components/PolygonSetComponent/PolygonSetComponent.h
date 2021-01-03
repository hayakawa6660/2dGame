#pragma once

#include "../ComponentBase.h"
#include <vector>
#include <array>
//�j�]���Ȃ��E��]�̃|���S���𐶐�����B
//���̃N���X���̂ɕ`��@�\�͖����̂Œ���
class PolygonSetComponent : public ComponentBase
{
public:
	PolygonSetComponent();
	~PolygonSetComponent();
private:
	std::vector<std::array<VECTOR, 4>> m_sqare;
public:
	//radiusY�͖{����Z�����A�񎟌����W�ōl���₷��Y�Ƃ��Ă���
	void SqareSet(VECTOR &_pos, float _radiusX, float _radiusY);
	std::array<VECTOR, 4> GetSqarePolygon(int _num)const { return m_sqare[_num]; }
};
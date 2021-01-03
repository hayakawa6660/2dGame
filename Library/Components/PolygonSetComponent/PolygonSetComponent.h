#pragma once

#include "../ComponentBase.h"
#include <vector>
#include <array>
//破綻しない右回転のポリゴンを生成する。
//このクラス自体に描画機能は無いので注意
class PolygonSetComponent : public ComponentBase
{
public:
	PolygonSetComponent();
	~PolygonSetComponent();
private:
	std::vector<std::array<VECTOR, 4>> m_sqare;
public:
	//radiusYは本当はZだが、二次元座標で考えやすくYとしている
	void SqareSet(VECTOR &_pos, float _radiusX, float _radiusY);
	std::array<VECTOR, 4> GetSqarePolygon(int _num)const { return m_sqare[_num]; }
};
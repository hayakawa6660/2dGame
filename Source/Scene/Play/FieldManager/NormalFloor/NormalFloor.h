#pragma once

#include "../FieldBase.h"

class NormalFloor : public FieldBase
{
public:
	NormalFloor(SceneBase * _scene);
	~NormalFloor();
private:
	void Update()override;
	void Draw()override;
private:
	float m_radius;
};
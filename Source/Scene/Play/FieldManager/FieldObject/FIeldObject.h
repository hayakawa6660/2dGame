#pragma once

#include "../FieldBase.h"

class FieldObject : public FieldBase
{
public:
	FieldObject(SceneBase * _scene);
	~FieldObject();
private:
	void Load()override;
	void Start()override;
	void Update()override;
};
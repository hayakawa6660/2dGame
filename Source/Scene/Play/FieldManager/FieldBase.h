#pragma once

#include "Library/GameObject/GameObject.h"

class FieldBase : public GameObject
{
public:
	FieldBase(SceneBase * _scene) : GameObject(_scene) {}
	virtual ~FieldBase(){}
private:
	virtual void Load()override{}
	virtual void Start()override{}
	virtual void Update()override{}
	virtual void Draw()override{}
};
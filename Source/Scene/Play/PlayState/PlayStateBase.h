#pragma once

#include "Library/GameObject/GameObject.h"

class PlayStateBase : public GameObject
{
public:
	PlayStateBase(SceneBase * _scene) : GameObject(_scene) {}
	virtual ~PlayStateBase() {}
	virtual void Load()override {}
	virtual void Start()override {}
	virtual void Update()override {}
};
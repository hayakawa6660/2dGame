#pragma once
#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"
#include <assert.h>
#include "PlayerMovement.h"

class PlayerStateBase;

class Player : public GameObject {
public:
	Player(SceneBase* _scene);
	~Player();
private:
	void Start()override;
	void Update()override;
	void Draw()override;

	PlayerStateBase* m_currentState;
	PlayerMovement m_movement;
	Sprite_Info m_texture;
public:
	template<class C>
	C* SetNextState() {
		C* obj = new C(GameObject::GetScene(), &m_movement);
		if (obj == nullptr)
			return obj;
		obj->SetParent(this);
		delete m_currentState;
		m_currentState = nullptr;
		m_currentState = obj;
		return obj;
	}
};

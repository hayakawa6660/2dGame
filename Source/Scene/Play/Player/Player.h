#pragma once

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

#include "State/PlayerMovement.h"

#include <assert.h>

class Shader;
class Player : public GameObject
{
public:
	Player(SceneBase * _scene);
	~Player();
	template<class C>
	C* ChangeState(std::string stateName) {
		C* nextState = new C;
		if (nextState) {
			nextState->SetParent(this);
			delete m_state;
			m_state = nullptr;
			m_state = nextState;
		}
	}
private:
	void Load()override;
	void Start()override;
	void Update()override;
	//描画関係
	void ShadowSetUp()override;
	void DrawSetUp()override;
	void Draw()override;

private:
	Model_Info m_model;
	//検索時間削減のコピーポインタ
	Shader * m_shader;
	MATRIX m_matrix;
	GameObject m_state;
};
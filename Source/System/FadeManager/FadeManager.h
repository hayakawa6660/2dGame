#pragma once

/*
�t�F�[�h�̊Ǘ�������N���X�B
�t�F�[�h�̌n���͂��ׂĂ�������ĂԁB
���̃N���X�Ɍ���A����I(��莞�ԈÂ����������Ȃ�)��Set�֐���F�߂�.


*****	�t�H���_�K�w	*****
souce > System > Fade
*/

#include "Library/GameObject/GameObject.h"
#include "Source/Common.h"

class FadeManager : public GameObject {
public:
	enum FADE_STATE {
		NO_STATE,
		FADE_IN,
		FADE_OUT,
	};
	FadeManager(SceneBase * _scene);
	~FadeManager();
	void Update()override;
	void Draw()override;

	//���̊֐��ɂ̂݃t�F�[�h��Set��F�߂�
	void FadeStart(int _fadeCount);
	void FadeIn();
	void FadeOut();

	void SetFadeLevel(float _fadeLevel);
private:
	int m_state;
	Sprite_Info m_texture;

	float m_fadeLevel;
	float m_fadeCount;
	bool m_fadeEnd;
public:
	bool IsFadeEnd()const { return m_fadeEnd; }
};
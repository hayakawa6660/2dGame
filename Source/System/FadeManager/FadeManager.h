#pragma once

/*
フェードの管理をするクラス。
フェードの系統はすべてここから呼ぶ。
このクラスに限り、限定的(一定時間暗くしたい時など)のSet関数を認める.


*****	フォルダ階層	*****
souce > System > Fade
*/

#include "../../../Library/GameObject/GameObject.h"
#include "../../Common.h"

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

	//この関数にのみフェードのSetを認める
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
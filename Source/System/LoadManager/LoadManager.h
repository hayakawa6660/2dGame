#pragma once

#include "../../../Library/GameObject/GameObject.h"
#include "../../Common.h"
#include <unordered_map>
/*
ロード画面を管理するクラス。
%表示や、
あるなら%ゲージ、TIPSの処理、表示を管理する。
*/

//#ifと、#elseはどっちにしようか悩んでいるところなので、
//出来ればどちらか、もしくは別の方法をご教授お願い致します。
class LoadManager : public GameObject
{
public:
	enum class SPRITE_TYPE
	{
		BACK_GROUND = 0,
		LOAD_CHARA,
	};
public:
	LoadManager(SceneBase * _scene);
	~LoadManager();

private:
	void Start()override;
	void Update()override;
	void Draw()override;

private:
	/// <summary>
	/// すべてのHandleのロードが終わっているかチェックする
	/// </summary>
	/// <return> 終わっていたらrue</return>
	bool LoadCheck();
private:
	bool m_isLoadEnd;
	Sprite_Info sprite;
	std::unordered_map<SPRITE_TYPE, Sprite_Info> m_imageList;
public:
	void SetActive(bool _flag);
};
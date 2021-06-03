#pragma once

#include "../ComponentBase.h"

#include <unordered_map>

//アニメーションがあるものは自身のクラスの下にこのクラスを継承
//して使う
class AnimationComponent : public ComponentBase
{
public:
	AnimationComponent();
	~AnimationComponent();
private:
	void Start()override {}
	void Update()override;
	void NormalUpdate();

	void BlendUpdate();
public:
	void BlendRateSpeed(const float& _blendSpeed) { m_blend.speed = _blendSpeed; }

	bool PlayingEnd();
	virtual bool PlayingAnimTypeEnd(const int& _handle);

	int GetCurrentAnimHandle();
	float GetTotalTime();
	float GetCurrentAnimTime();

	void Play(std::string _animName, const float& _speed = 0.5f);
	void SetBlendFlag(bool _flag) { m_blendFlag = _flag; }
	void SetPlaySpeed(const float& _speed);
	void SetBlendSpeed(const float& _speed);
	void Stop(bool _stop) { m_stop = _stop; }
	void SetBody(int _model) { m_model = _model; }
	void SetAnim(std::string _animName, int _handle) { if (!m_animList.count(_animName)) m_animList[_animName] = _handle; }
	void SetReverce(bool _flag) { m_reverse = _flag; }
	//移動量等、移動や回転に関わるもの
	/// <summary>
	/// 現在再生しているアニメーションで移動した分のローカルのポジションを取得する。
	/// ローカルの原点からの移動量なので注意
	/// </summary>
	/// <param name="_frameName">取得したいポジションのボーン(フレーム名)</param>
	VECTOR GetFramePosition(const std::string &_frameName);

	/// <summary>
	/// アニメーションの移動量を取得する。
	/// 前回呼んだGetMoveFrameからの差分が返ってくる(移動量)
	/// 尚、差分はアニメーションループ時に自動的に0に戻るので
	/// 原点に戻る様なアニメーションループにも対応している。
	/// ※ 呼ぶたびに差分が更新されるので1フレーム呼ばなかった場合、2フレーム分の移動量が返る
	/// </summary>
	/// <param name="_frameName">取得したいポジションのボーン(フレーム名)</param>
	/// <param name="_fixd">指定ボーン(フレーム)ポジションを0に固定するか</param>
	VECTOR GetMoveFrame(const std::string &_frameName, bool _fixed = false);
	/// <summary>
	/// 指定フレームをローカルポジション0に設定する。
	/// 主にrootを固定するために使う
	/// </summary>
	/// <param name="_frameName">取得したいポジションのボーン(フレーム名)</param>
	void GetFrameZeroVector(const std::string &_frameName);
private:
	//自分でアニメーションのハンドルを持つのも馬鹿馬鹿しいのでこちらに持っておく
	std::unordered_map<std::string, int> m_animList;
	int		m_model;
	int		m_nextAnim;		//一時的にモデルのハンドルを保管
	int		m_currentAnim;	//今再生しているアニメーションのハンドル
	int		m_currentIndex;	//アニメーションした後
	float	m_playSpeed;	//アニメーションのスピード
	float	m_currentTime;	//今のアニメーションのフレーム	
	float	m_totalTime;	//アタッチされたアニメーションの総フレーム
	bool	m_blendFlag;
	bool	m_stop;			//アニメーションをストップするかどうか
	bool	m_reverse;		//逆再生させるかどうか

	struct BLEND_ANIM_INFO {
		int		index;		//アニメーションする前
		float	rate;		//ブレンド率
		float	speed;
		BLEND_ANIM_INFO() :
			index(-1), rate(0.f), speed(0.2f) {}
	};
	BLEND_ANIM_INFO m_blend;

	//移動、差分等
	VECTOR m_prevPos;
};
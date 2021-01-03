#pragma once

#include <EffekseerForDXLib.h>

#include "Library/GameObject/GameObject.h"

#include <DxLib.h>
#include <unordered_map>
#include <list>
#include <assert.h>
#include <string>

class MyEffekseer :public GameObject {
public:
	MyEffekseer(SceneBase * _scene);
	~MyEffekseer();
	void Update();
	void Draw();
	void Release();

	bool IsEffectPlaying(int _handle);
	void Load(const char* _fileName);

	int PlayEffect(const std::string& _key, const VECTOR& _pos = { 0,0,0 }, const float& _scale = 1.f);
	void AutoEffectDelete();
	void SetPosition(const int& _handle, const VECTOR& _pos);
	void SetRotation(const int& _handle, const VECTOR& _rot);
	void SetScale(const int& _handle, const VECTOR& _scale);
	float GetSpeed(int _handle);
	void SetSpeed(int _handle, const float& speed);
	int DestroyEffect(const int _handle);
	int StopEffect(const int _handle);
	void SetMatrix(int _handle, const MATRIX& _m);
	///<summary>
	///使用中のインスタンスの数を取得
	///</summary>
	///<return>
	///使用インスタンス数
	///<return>
	int SecureInstance();
private:
	///<summary>
	///DxLibの行列をEffekseerの行列に変換する
	///</summary>
	///<return>
	///変換されたEffekseerの行列
	///</return>
	Effekseer::Matrix43 DxLib_MATRIXToEffekseer_Matrix43Conversion(const MATRIX& _m);
private:
	std::list<int> m_playingEffectHandle;
	int m_firstDrawImage;

	std::unordered_map<std::string, int> m_effectData;

};
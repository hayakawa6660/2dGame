#pragma once

#include "../../../../Library/GameObject/GameObject.h"
#include "../../../Common.h"
#include <unordered_map>

class Sounds : public GameObject
{
public:
	Sounds(SceneBase * _scene);
	~Sounds();

	void Update()override;
	/// <summary>
	/// 指定したサウンドのロードを行う
	/// サウンドをプレイする場合は、ここで送った_pathの名前を使う
	/// </summary>
	/// <param name="_fileName">ファイルのパス</param>
	/// <param name="_path">呼び出す時に使う名前</param>
	void Load(std::string _folder, std::string _csv);
	/// <summary>
	/// タグの一致したサウンドを再生する
	/// </summary>
	/// <param name="_tag">鳴らしたいサウンドのファイル名</param>
	void SoundPlay(std::string _tag);	//PlaySoundはDxLIb関数にあったので使えない
	/// <summary>
	/// タグの一致したサウンドを停止する
	/// </summary>
	/// <param name="_tag">鳴らしたいサウンドのファイル名</param>
	void StopSound(std::string _tag);
	/// <summary>
	/// 全てのサウンドを停止する
	/// </summary>
	void AllStop();

private:
	bool m_isLoadEnd;
	bool m_isScene;
	std::unordered_map<std::string, Sound_Info> m_soundList;
public:
	void CheckScene();
};
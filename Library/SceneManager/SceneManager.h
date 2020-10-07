#pragma once

#include <string>
#include <list>

class SceneFactory;
class SceneBase;

/// <summary>
/// 現在のシーンを呼び出している。
/// Sceneを切り替える時は、ChangeScene()を呼び出せばよく、
/// 呼んだ時に切り替えるのではなく、次回のUpdate()で切り替えるようにしている。
/// </summary>
class SceneManager {
private:
	SceneManager();
public:
	static SceneManager* GetInstance();
	void Start();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// シーンを切り替える。
	/// 直接ここでは切り替えず、次回Update()が呼ばれたとき、Scene処理を呼ぶ前に切り替えます。
	/// シーンの名前とクラスの関係は、SceneFactory()に記述してください。
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	void ChangeScene(const std::string& sceneName);
private:
	std::string m_currentName;	// 現在のシーンの名称
	std::string m_nextName;		// 次のシーンの名称
	SceneBase* m_currentScene;	// 今のシーンのインスタンスを保持
	SceneFactory* m_factory;	// シーン切り替え用のFactoryのポインター
	bool m_exit;				//ゲームが終了したか
public:
	/// <summary>
	//現在のインスタンスのシーンを取得する
	/// </summary>
	SceneBase * GetCurrentScene()const { return m_currentScene; }
	void Exit() { m_exit = true; }
	bool IsExit()const { return m_exit; }
};

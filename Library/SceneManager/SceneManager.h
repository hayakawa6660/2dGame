#pragma once

#include <string>
#include <list>

class SceneFactory;
class SceneBase;

/// <summary>
/// ���݂̃V�[�����Ăяo���Ă���B
/// Scene��؂�ւ��鎞�́AChangeScene()���Ăяo���΂悭�A
/// �Ă񂾎��ɐ؂�ւ���̂ł͂Ȃ��A�����Update()�Ő؂�ւ���悤�ɂ��Ă���B
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
	/// �V�[����؂�ւ���B
	/// ���ڂ����ł͐؂�ւ����A����Update()���Ă΂ꂽ�Ƃ��AScene�������ĂԑO�ɐ؂�ւ��܂��B
	/// �V�[���̖��O�ƃN���X�̊֌W�́ASceneFactory()�ɋL�q���Ă��������B
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	void ChangeScene(const std::string& sceneName);
private:
	std::string m_currentName;	// ���݂̃V�[���̖���
	std::string m_nextName;		// ���̃V�[���̖���
	SceneBase* m_currentScene;	// ���̃V�[���̃C���X�^���X��ێ�
	SceneFactory* m_factory;	// �V�[���؂�ւ��p��Factory�̃|�C���^�[

	bool m_exitGame;			//�Q�[�����I������
	bool m_exit;				//�Q�[��������ɏI��������true��Ԃ�
public:
	/// <summary>
	//���݂̃C���X�^���X�̃V�[�����擾����
	/// </summary>
	SceneBase * GetCurrentScene()const { return m_currentScene; }
	void ExitGame() { m_exitGame = true; }
	bool IsGameExit()const { return m_exitGame; }
	bool IsExit()const { return m_exit; }
};

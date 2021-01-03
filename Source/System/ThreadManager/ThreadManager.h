#pragma once

#include "Library/GameObject/GameObject.h"

#include <thread>
#include <unordered_map>
#include <functional>

//�X���b�h���g�p����ꍇ�́A�Q�[�������S�ɏI�����邽�߁A
//�K�����̃N���X��ʂ��Č��݉��X���b�h���g���Ă��邩���m�F��
//�X���b�h���I�������ꍇ�A���̃N���X�ɏI����`����
class ThreadManager : public GameObject
{
public:
	ThreadManager(SceneBase * _scene) : m_num(0), m_allEnd(false) {}
	~ThreadManager() {}

	void StartThread() { ++m_num; }
	void EndThread() { --m_num; }
	void AllEnd() { m_allEnd = true; }
	bool IsAllEnd()const { return m_allEnd; }
	int CurrentNum()const { return m_num; }

	template<typename T>
	void CreateThread(std::function<T()> _func)
	{
		m_num++;
		std::thread th(_func);
		th.detach();
	}
private:
	int m_num;
	bool m_allEnd;
};
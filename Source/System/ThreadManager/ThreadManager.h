#pragma once

#include "Library/GameObject/GameObject.h"

#include <thread>
#include <unordered_map>
#include <functional>

//スレッドを使用する場合は、ゲームを安全に終了するため、
//必ずこのクラスを通して現在何個スレッドを使っているかを確認し
//スレッドが終了した場合、このクラスに終了を伝える
class ThreadManager : public GameObject
{
public:
	ThreadManager(SceneBase * _scene) : m_num(0), m_allEnd(false) {}
	~ThreadManager() {}

	//void StartThread() { ++m_num; }
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
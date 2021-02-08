#pragma once

#include "Library/SceneManager/SceneBase.h"
#include <mutex>

class ThreadManager;
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
private:
	void Update()override;
	void Draw()override;
	void NewClasses();
	//void DrawFString(int _x, int _y, const char * _format...);
private:
	std::list<GameObject*> m_list;
	bool m_isNewEnd;
	ThreadManager * m_thread;
	enum class STATE
	{
		NEW = 0,
		LOAD,
		PLAY,
		CHANGE,
	};
	STATE m_state;
};
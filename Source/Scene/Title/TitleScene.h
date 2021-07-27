#pragma once

#include "Library/SceneManager/SceneBase.h"
#include <mutex>
#include "Source/Common.h"

class ThreadManager;
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
private:
	void Update()override;
	void Load();
	//void DrawFString(int _x, int _y, const char * _format...);
private:
	std::list<GameObject*> m_list;

	Sprite_Info m_sprite;

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
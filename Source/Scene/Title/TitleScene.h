#pragma once

#include "Library/SceneManager/SceneBase.h"
#include <mutex>

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
private:
	void Update()override;
	void Draw()override;
	void DrawFString(int _x, int _y, const char * _format...);
private:
	std::list<GameObject*> m_list;
};
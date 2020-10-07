#pragma once

#include "../../../../Library/GameObject/GameObject.h"

#include <vector>
#include <iostream>

class DebugClasses : public GameObject
{
public:
	DebugClasses(SceneBase * _scene);
	~DebugClasses();
private:
	void Draw()override;
private:
	struct String_Info
	{
		std::string str;
		int x, y;
	};
	std::list<String_Info> m_strList;
	bool m_active;
public:
	void Puts(int _x, int _y, const char * _format, ...);
	void ChangeActive() { m_active = !m_active; }
	bool GetActive()const { return m_active; }
	void SetActive(bool _active) { m_active = _active; }
};
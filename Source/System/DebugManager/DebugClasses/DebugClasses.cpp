#include "DebugClasses.h"

#include "Library/Common/commonObjects.h"
#include "../../DebugManager/DebugManager.h"

DebugClasses::DebugClasses(SceneBase * _scene) :
	GameObject(nullptr),
	m_active(false)
{
	m_strList.clear();
}

DebugClasses::~DebugClasses()
{
	m_strList.clear();
}

void DebugClasses::Draw()
{
	if (!m_active)
	{
		m_strList.clear();
		return;
	}

	for (auto &it : m_strList)
	{
		DrawFormatString(it.x, it.y, 0xffffff, it.str.c_str());
	}
	if (!Debug::GetFactorFlag("GameStop"))
		m_strList.clear();
}

void DebugClasses::Puts(int _x, int _y, const char * _format, ...)
{
	String_Info info;
	info.x = _x;
	info.y = _y;
	info.str = _format;
	m_strList.emplace_back(info);
}
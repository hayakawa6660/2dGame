#include "DebugClasses.h"

#include "Library/Common/commonObjects.h"
#include "../../DebugManager/DebugManager.h"
#include "Library/Render/RenderManager.h"

DebugClasses::DebugClasses(SceneBase * _scene) :
	GameObject(nullptr),
	m_active(false)
{
	m_strList.clear();
	//テキスト描画をセットアップ
	RenderManager::GetInstance()->AddText("DebugClasses", [=]()
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
	});
}

DebugClasses::~DebugClasses()
{
	//テキスト描画を消去
	RenderManager::GetInstance()->RemoveText("DebugClasses");
	m_strList.clear();
}
/*
void DebugClasses::Draw()
{
	if (!m_active)
	{
		m_strList.clear();
		return;
	}

	for (auto &it : m_strList)
	{
		DrawFormatString(info.x, info.y, 0xffffff, info.str.c_str());
	}
	if (!Debug::GetFactorFlag("GameStop"))
		m_strList.clear();
}
*/
void DebugClasses::Puts(int _x, int _y, const char * _format, ...)
{
	String_Info info;
	info.x = _x;
	info.y = _y;
	info.str = _format;
	m_strList.emplace_back(info);
}
#include "DebugManager.h"
#include "DebugClasses/DebugClasses.h"

#include "Library/Common/commonObjects.h"
#include "../InputManager/InputManager.h"
#include "Library/Render/RenderManager.h"

#include <stdarg.h>
#include <stdio.h>

DebugManager::DebugManager(SceneBase* _scene) :
	GameObject(nullptr),
	m_menuNum(0),
	m_currentNum(0),
	m_isDebugMode(false),
	m_allDestroy(false)
{
	m_active.clear();
	m_active.emplace("Reset", false);
	m_active.emplace("GameStop", false);
	m_debugList.clear();

	//テキスト描画をセットアップ
	RenderManager::GetInstance()->AddText("DebugManager", [=]()
	{
		if (!m_isDebugMode)
			return;
		DrawFormatString(0, 0, 0xffffff, "DebugMode");
		DrawFormatString(0, 20 + (20 * m_currentNum), 0xffffff, ">");

		int num = 0;
		for (auto &it : m_active)
		{
			char ch[256];
			sprintf_s<256>(ch, " %d", it.second);
			std::string str = it.first + ch;

			DrawFormatString(15, 20 + (num * 20), 0xffffff, str.c_str());
			num++;
		}
		num = (int)m_active.size();
		for (auto &it : m_debugList)
		{
			char ch[256];
			sprintf_s<256>(ch, " %d", it->GetActive());
			std::string str = it->GetTag() + ch;
			DrawFormatString(15, 20 + (num * 20), 0xffffff, str.c_str());
			num++;
		}
	});
}

DebugManager::~DebugManager()
{
	RenderManager::GetInstance()->RemoveText("DebugManager");
	m_active.clear();
	m_debugList.clear();
}

void DebugManager::Update()
{
	DestroyUpdate();
	InputManager * p = CommonObjects::GetInstance()->FindGameObject<InputManager>("InputManager");
	if (p->IsTrigger("DEBUG"))
		m_isDebugMode = !m_isDebugMode;
	if (!m_isDebugMode)
		return;

	ResetUpdate();
	SelectUpdate();
}

void DebugManager::SelectUpdate()
{
	InputManager * p = CommonObjects::GetInstance()->FindGameObject<InputManager>("InputManager");
	//上下選択
	if (p->IsTrigger("UP"))
		m_currentNum = (m_currentNum + m_menuNum + (int)m_active.size() - 1) % (m_menuNum + (int)m_active.size());
	else if (p->IsTrigger("DOWN"))
		m_currentNum = (m_currentNum + 1) % (m_menuNum + (int)m_active.size());

	//決定(ON、OFFの切り替え)
	if (p->IsTrigger("RIGHT"))
	{
		if (m_currentNum < (int)m_active.size())
		{
			int a = 0;
			for (auto &it : m_active)
			{
				if (m_currentNum != a)
				{
					a++;
					continue;
				}
				it.second = !it.second;
				break;
			}
		}
		else
		{
			int a = (int)m_active.size();
			for (auto &it : m_debugList)
			{
				if (a != m_currentNum)
				{
					a++;
					continue;
				}
				it->ChangeActive();
				break;
			}
		}
	}
}

void DebugManager::ResetUpdate()
{
	if (!m_active["Reset"])
		return;
	for (auto &it : m_active)
		it.second = false;
	for (auto &it : m_debugList)
		it->SetActive(false);

}

void DebugManager::DestroyUpdate()
{
	//全て消すフラグが立っていたら
	if (!m_allDestroy)
		return;
	//全ての要素を削除する
	for (auto &it = m_active.begin(); it != m_active.end();)
	{
		if (it->first == "Reset" || it->first == "GameStop")
		{
			it++;
			continue;
		}
		it = m_active.erase(it);
	}

	m_currentNum = 0;
	for (auto it = m_debugList.begin(); it != m_debugList.end();)
	{
		if ((*it)->IsDestroy())
		{
			it = m_debugList.erase(it);
			m_menuNum--;
		}
		else
		{
			it++;
		}
	}
	m_allDestroy = false;
}

void DebugManager::SetActive(std::string & _className, bool _active)
{
	for (auto &it : m_debugList)
	{
		if (it->GetTag() != _className)
			continue;
		it->SetActive(_active);
		break;
	}
}

void DebugManager::Puts(int _x, int _y, std::string _classTag, const char * _format, ...)
{
	CommonObjects * common = CommonObjects::GetInstance();
	DebugClasses * debug = common->FindGameObject<DebugClasses>(_classTag);
	if (debug == nullptr)
	{
		debug = common->CreateGameObject<DebugClasses>(_classTag);
		common->SetDrawOrder(debug, 10000);
		m_menuNum++;
		m_debugList.emplace_back(debug);
	}
	debug->Puts(_x, _y, _format);
}

void DebugManager::ListAllClear()
{
	for (auto &it : m_debugList)
	{
		it->DestroyMe();
	}
	m_allDestroy = true;
}

bool DebugManager::GetFactorFlag(std::string _factorName)
{
	if (m_active.count(_factorName) == FALSE)	//同じ名前のキーがあればは登録しない
		m_active[_factorName] = false;

	return m_active[_factorName];
}

void Debug::SetActive(std::string _className, bool _active)
{
	CommonObjects::GetInstance()->FindGameObject<DebugManager>("DebugManager")->SetActive(_className, _active);
}

void Debug::VSOutputLog(const char *_format ...)
{
	va_list vlist;
	char ch[256];
	va_start(vlist, _format);
	vsprintf_s(ch, _format, vlist);
	OutputDebugString(ch);
	OutputDebugString("\n");
	va_end(vlist);
}

void Debug::DebugPrintf(int _x, int _y, std::string _classTag, const char *_format...)
{
	va_list vlist;
	char ch[256];
	va_start(vlist, _format);
	vsprintf_s(ch, _format, vlist);
	CommonObjects::GetInstance()->FindGameObject<DebugManager>("DebugManager")
		->Puts(_x, _y, _classTag, ch);
	va_end(vlist);
}

bool Debug::GetFactorFlag(std::string _factorName)
{
	return 	CommonObjects::GetInstance()->FindGameObject<DebugManager>("DebugManager")->GetFactorFlag(_factorName);
}

void Debug::ListAllClear()
{
	CommonObjects::GetInstance()->FindGameObject<DebugManager>("DebugManager")->ListAllClear();
}
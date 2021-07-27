#include "CacheManager.h"

#include "../DebugManager/DebugManager.h"
#include "Library/Common/commonObjects.h"
#include "Source/System/InputManager/InputManager.h"
#include "Library/Render/RenderManager.h"

CacheManager::CacheManager(SceneBase * _scene) :
	GameObject(nullptr)
{
	m_cache.clear();
#if DEBUG
	RenderManager::GetInstance()->AddText("CacheManagerText", [=]()
	{
		int i = 0;
		for (auto& it : m_cache)
		{
			char ch[256];
			sprintf_s<256>(ch, "\nsampleNum %d | time %05lldus | ave %lldus | min %lldus | max %lldus",
				it.second.num, it.second.time, it.second.average, it.second.minTime, it.second.maxTime);
			std::string str = it.first + ch;
			Debug::DebugPrintf(150, 20 + (i * 40), "Cache", str.c_str());
			++i;
		}
		Debug::DebugPrintf(180, 0, "Cache", "Cache");
	});
#endif
}

CacheManager::~CacheManager()
{
	m_cache.clear();
}

void CacheManager::Start()
{
	Debug::SetActive("Cache", true);
}

void CacheManager::Update()
{
#if DEBUG
	if (CommonObjects::GetInstance()->FindGameObject<InputManager>("InputManager")
		->IsTrigger("LSHIFT"))
		m_cache.clear();
#endif
}

void CacheManager::EndTime(std::string &_cacheName)
{
	auto &it = m_cache[_cacheName];
	QueryPerformanceCounter(&it.after);
	it.time = ((it.after.QuadPart - it.before.QuadPart) * 1000000L) / it.qpf.QuadPart;
	//É}ÉCÉNÉçïbÇ≈éÊìæÇ∑ÇÈ
	if (it.num < 1000)
	{
		it.total += it.time;

		it.num++;
		it.average = it.total / it.num;
	}
	if (it.time <= it.minTime || it.minTime == 0)
		it.minTime = it.time;
	if (it.time >= it.maxTime || it.maxTime == 0)
		it.maxTime = it.time;
}

void CacheManager::StartTime(std::string &_cacheName)
{
	auto &it = m_cache[_cacheName];
	memset(&it.qpf, 0, sizeof it.qpf);
	memset(&it.before, 0, sizeof it.before);
	memset(&it.after, 0, sizeof it.after);
	it.time = 0;
	QueryPerformanceFrequency(&it.qpf);
	QueryPerformanceCounter(&it.before);
}

void Cache::StartTime(std::string _cacheName)
{
	CommonObjects::GetInstance()->FindGameObject<CacheManager>("CacheManager")
		->StartTime(_cacheName);
}

void Cache::EndTime(std::string _cacheName)
{
	CommonObjects::GetInstance()->FindGameObject<CacheManager>("CacheManager")
		->EndTime(_cacheName);
}

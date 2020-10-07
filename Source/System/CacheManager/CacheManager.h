#pragma once

#include "../../../Library/GameObject/GameObject.h"

#include <map>

class CacheManager : public GameObject
{
public:
	CacheManager(SceneBase * _scene);
	~CacheManager();

private:
	void Update()override;

private:
	struct Cache_Info
	{
		LARGE_INTEGER qpf, before, after;
		int num;
		long long total;
		long long time;
		long long average;
		long long maxTime;
		long long minTime;
		Cache_Info() :
			qpf(LARGE_INTEGER()),
			before(LARGE_INTEGER()),
			after(LARGE_INTEGER()),
			num(0),
			total(0),
			time(0),
			average(0),
			maxTime(0),
			minTime(0)
		{}
	};
	//様々なキャッシュを管理すると思うのでmap
	std::map<std::string, Cache_Info> m_cache;
public:
	/// <summary>
	/// 処理前の時間をセットする
	/// </summary>
	/// <param name="_cacheName">処理する時間計測の名前</param>
	void StartTime(std::string &_cacheName);
	void EndTime(std::string &_cacheName);
};

namespace Cache
{
	/// <summary>
	/// 処理前の時間をセットする
	/// </summary>
	/// <param name="_cacheName">処理する時間計測の名前</param>
	void StartTime(std::string _cacheName);
	void EndTime(std::string _cacheName);
}
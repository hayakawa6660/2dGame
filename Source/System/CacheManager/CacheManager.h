#pragma once

#include "Library/GameObject/GameObject.h"

#include <map>

class CacheManager : public GameObject
{
public:
	CacheManager(SceneBase * _scene);
	~CacheManager();

private:
	void Start()override;
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
	//�l�X�ȃL���b�V�����Ǘ�����Ǝv���̂�map
	std::map<std::string, Cache_Info> m_cache;
public:
	/// <summary>
	/// �����O�̎��Ԃ��Z�b�g����
	/// </summary>
	/// <param name="_cacheName">�������鎞�Ԍv���̖��O</param>
	void StartTime(std::string &_cacheName);
	void EndTime(std::string &_cacheName);
};

namespace Cache
{
	/// <summary>
	/// �����O�̎��Ԃ��Z�b�g����
	/// </summary>
	/// <param name="_cacheName">�������鎞�Ԍv���̖��O</param>
	void StartTime(std::string _cacheName);
	void EndTime(std::string _cacheName);
}
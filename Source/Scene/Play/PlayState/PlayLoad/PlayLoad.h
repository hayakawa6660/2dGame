#pragma once

#include "../PlayStateBase.h"

class PlayLoad : public PlayStateBase
{
public:
	PlayLoad(SceneBase * _scene);
	~PlayLoad();
private:
	void Load()override;
	void Start()override;
	void Update()override;
	void Draw()override;
private:
	bool m_canNext;

	enum class STATE
	{
		UNZIP,
		LOAD,
		END,
	};
	STATE m_state;
};
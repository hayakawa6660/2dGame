#pragma once

#include "Library/SceneManager/SceneBase.h"
class PlayStateBase;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
private:
	void Update()override;
	void Load();

	void ChangeState();
public:
	template<class C>
	C* SetNextState(std::string _str)
	{
		C* p = new C(this);
		p->SetTag(_str);
		m_next = p;
		return p;
	}
	void GameObjectUpdate();
private:
	PlayStateBase* m_current;
	PlayStateBase* m_next;
};
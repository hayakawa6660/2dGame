#pragma once

#include "Library/GameObject/GameObject.h"

class FieldBase;

class FieldManager : public GameObject
{
public:
	FieldManager(SceneBase * _scene);
	~FieldManager();
private:
	void Update()override;
private:
	std::list<FieldBase*> m_fieldList;
	bool m_listDestroy;
public:
	void FieldDestroy() { m_listDestroy = true; }
};
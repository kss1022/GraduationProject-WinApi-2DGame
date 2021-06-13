#pragma once
#include "Object.h"

class StaticObject :public Object
{
protected:
	StaticObject();
	StaticObject(const StaticObject& obj);
	virtual ~StaticObject();

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	StaticObject*	 Clone() = 0;

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};


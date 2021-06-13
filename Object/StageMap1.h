#pragma once
#include "StaticObject.h"

class StageMap1 : public StaticObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	StageMap1();
	StageMap1(const StageMap1& obj);
	virtual ~StageMap1();

public:
	virtual bool Init() ;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	StageMap1*	 Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

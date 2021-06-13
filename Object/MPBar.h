#pragma once
#include "MoveObject.h"
class MPBar :
	public MoveObject
{
private:
	friend class Object;
	friend class Scene;

protected:
	MPBar();
	MPBar(const MPBar& obj);
	virtual ~MPBar();

	Object* m_pObject;
	float m_fMP;
	float m_fMPMAX;

public:
	Object* GetObject_() const;
	void SetObject(class Object* obj);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	MPBar*	 Clone();
};


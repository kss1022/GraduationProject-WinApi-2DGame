#pragma once
#include "Collider.h"
class ColliderReact : public Collider
{
private:
	friend class Object;

protected:
	ColliderReact();
	ColliderReact(const ColliderReact& coll);

	virtual ~ColliderReact();



public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	ColliderReact*	 Clone();


	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
private:
	RECTANGLE m_tInfo;
	RECTANGLE m_tWorldInfo;
	_SIZE		m_tColliderOffset;

public:
	inline void  SetRect(float l, float t, float r, float b);
	inline RECTANGLE GetInfo() const;
	inline RECTANGLE GetWorldInfo() const;
	inline void	SetCollierOffset(float x, float y);
};

void ColliderReact::SetRect(float l, float t, float r, float b)
{
	m_tInfo.l = l;
	m_tInfo.t = t;
	m_tInfo.r = r;
	m_tInfo.b = b;
}

RECTANGLE ColliderReact::GetInfo() const
{
	return m_tInfo;
}

RECTANGLE ColliderReact::GetWorldInfo() const
{
	return m_tWorldInfo;
}

void ColliderReact::SetCollierOffset(float x, float y)
{
	m_tColliderOffset.x = x;
	m_tColliderOffset.y = y;
}

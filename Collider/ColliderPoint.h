#pragma once
#include "Collider.h"
class ColliderPoint :
	public Collider
{
private:
	friend class Object;

protected:
	ColliderPoint();
	ColliderPoint(const ColliderPoint& coll);

	virtual ~ColliderPoint();

private:
	POSITION	m_tDist;
	POSITION	m_tPos;

public:
	inline void SetDistance(float x, float y);
	inline void SetDistance(const POSITION& point);
	inline POSITION GetPoint() const;
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	ColliderPoint*	 Clone();


	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

void ColliderPoint::SetDistance(float x, float y)
{
	m_tDist.x = x;
	m_tDist.y = y;
}

void ColliderPoint::SetDistance(const POSITION & point)
{
	m_tDist = point;
}

inline POSITION ColliderPoint::GetPoint() const
{
	return m_tPos;
}

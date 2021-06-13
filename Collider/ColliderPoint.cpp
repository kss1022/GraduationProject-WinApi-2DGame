#include "ColliderPoint.h"
#include "../Object/Object.h"
#include "ColliderSphere.h"
#include "ColliderPixel.h"
#include "ColliderReact.h"

ColliderPoint::ColliderPoint()
{
	m_eCollType = CT_POINT;
}

ColliderPoint::ColliderPoint(const ColliderPoint & coll) : Collider(coll)
{
	m_eCollType = coll.m_eCollType;
	m_tDist = coll.m_tDist;
}

ColliderPoint::~ColliderPoint()
{
}



bool ColliderPoint::Init()
{
	return true;
}

void ColliderPoint::Input(float fDeltaTime)
{
	Collider::Input(fDeltaTime);
}

int ColliderPoint::Update(float fDeltaTime)
{
	Collider::Update(fDeltaTime);
	return 0;
}

int ColliderPoint::LateUpdate(float fDeltaTime)
{
	Collider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObject->GetPos();
	
	m_tPos.x = tPos.x + m_tDist.x;
	m_tPos.y = tPos.y + m_tDist.y;

	return 0;
}

bool ColliderPoint::Collision(Collider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_REACT:
		return Collider::CollisionReactToPoint(((ColliderReact*)pDest)->GetWorldInfo() , m_tPos);
			break;
	case CT_SPEARE:
		return Collider::CollisionSphereToPoint(((ColliderSphere*)pDest)->GetWorldInfo(), m_tPos);
		break;
	case CT_PIXEL:		
		return Collider::CollisionPixelToPoint(((ColliderPixel*)pDest)->GetPixel(), ((ColliderPixel*)pDest)->GetWidth(), (
			(ColliderPixel*)pDest)->GetHeight(), m_tPos);
		break;

	default:
		break;
	}

	return false;
}

void ColliderPoint::Render(HDC hDC, float fDeltaTime)
{
	Collider::Render(hDC, fDeltaTime);

	
}

ColliderPoint * ColliderPoint::Clone()
{
	return new ColliderPoint(*this);
}

void ColliderPoint::Save(FILE * pFile)
{
	Collider::Save(pFile);
}

void ColliderPoint::Load(FILE * pFile)
{
	Collider::Load(pFile);
}



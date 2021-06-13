#include "ColliderSphere.h"
#include "../Object/Object.h"
#include "ColliderReact.h"
#include "ColliderPixel.h"
#include "ColliderPoint.h"
#include "../Core/Camera.h"

ColliderSphere::ColliderSphere()
{
	m_eCollType = CT_SPEARE;
}

ColliderSphere::ColliderSphere(const ColliderSphere & collSphere) : Collider(collSphere)
{
	m_tInfo = collSphere.m_tInfo;
	m_eCollType = collSphere.m_eCollType;
}

ColliderSphere::~ColliderSphere()
{
}

bool ColliderSphere::Init()
{
	return true;
}

void ColliderSphere::Input(float fDeltaTime)
{
	Collider::Input(fDeltaTime);
}

int ColliderSphere::Update(float fDeltaTime)
{
	Collider::Update(fDeltaTime);
	return 0;
}

int ColliderSphere::LateUpdate(float fDeltaTime)
{
	Collider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObject->GetPos();

	m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
	m_tWorldInfo.fRadius = m_tInfo.fRadius;
	return 0;
}

bool ColliderSphere::Collision(Collider * pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_SPEARE:
		return CollisionSphereToSphere(m_tWorldInfo, ((ColliderSphere*)pDest)->GetWorldInfo());
		break;
	case  CT_REACT:
		return CollisionReactToSphere(((ColliderReact*)pDest)->GetWorldInfo(), m_tWorldInfo);
		break;
	case CT_PIXEL:
		return CollisionSphereToPoint(m_tWorldInfo, ((ColliderPoint*)pDest)->GetPoint());
		break;
	default:
		break;
	}


	return false;
}

void ColliderSphere::Render(HDC hDC, float fDeltaTime)
{
	Collider::Render(hDC, fDeltaTime);
#ifdef _DEBUG

	POSITION CameraPos = Camera::GetInst()->GetPos();

	MoveToEx(hDC, (m_tWorldInfo.tCenter.x - m_tWorldInfo.fRadius) - CameraPos.x, m_tWorldInfo.tCenter.y - CameraPos.y, nullptr);
	LineTo(hDC, (m_tWorldInfo.tCenter.x + m_tWorldInfo.fRadius) - CameraPos.x, m_tWorldInfo.tCenter.y - CameraPos.y);

	MoveToEx(hDC, m_tWorldInfo.tCenter.x - CameraPos.x, (m_tWorldInfo.tCenter.y - m_tWorldInfo.fRadius) - CameraPos.y, nullptr);
	LineTo(hDC, m_tWorldInfo.tCenter.x - CameraPos.x, (m_tWorldInfo.tCenter.y + m_tWorldInfo.fRadius) - CameraPos.y);
#endif // _DEBUG

}

ColliderSphere * ColliderSphere::Clone()
{
	return new ColliderSphere(*this);
}

void ColliderSphere::Save(FILE * pFile)
{
	Collider::Save(pFile);
}

void ColliderSphere::Load(FILE * pFile)
{
	Collider::Load(pFile);
}

#include "ColliderReact.h"
#include "../Object/Object.h"
#include "ColliderSphere.h"
#include "ColliderPixel.h"
#include "ColliderPoint.h"
#include "../Core/Camera.h"

ColliderReact::ColliderReact()
	:m_tColliderOffset(0.f, 0.f)
{
	m_eCollType = CT_REACT;
}

ColliderReact::ColliderReact(const ColliderReact & collRect) : Collider(collRect)
{
	m_tInfo = collRect.m_tInfo;
	m_eCollType = collRect.m_eCollType;
	m_tColliderOffset = collRect.m_tColliderOffset;
}

ColliderReact::~ColliderReact()
{
}

bool ColliderReact::Init()
{
	return true;
}

void ColliderReact::Input(float fDeltaTime)
{
	Collider::Input(fDeltaTime);
}

int ColliderReact::Update(float fDeltaTime)
{
	Collider::Update(fDeltaTime);
	return 0;
}

int ColliderReact::LateUpdate(float fDeltaTime)
{
	Collider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObject->GetPos();

	m_tWorldInfo.l = tPos.x + m_tInfo.l + m_tColliderOffset.x;
	m_tWorldInfo.t = tPos.y + m_tInfo.t + m_tColliderOffset.y;
	m_tWorldInfo.r = tPos.x + m_tInfo.r + m_tColliderOffset.x;
	m_tWorldInfo.b = tPos.y + m_tInfo.b + +m_tColliderOffset.y	;

	return 0;
}

bool ColliderReact::Collision(Collider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_REACT:
		return CollisionReactToReact(m_tWorldInfo, ((ColliderReact*)pDest)->GetWorldInfo());
		break;
	case CT_SPEARE:
		return CollisionReactToSphere(m_tWorldInfo, ((ColliderSphere*)pDest)->GetWorldInfo());
		break;
	case CT_PIXEL:
		return CollisionReactToPixel(m_tWorldInfo, ((ColliderPixel*)pDest)->GetPixel(),
			((ColliderPixel*)pDest)->GetWidth(), ((ColliderPixel*)pDest)->GetHeight());
		break;
	case CT_POINT:
		return  CollisionReactToPoint(m_tWorldInfo, ((ColliderPoint*)pDest)->GetPoint());
	default:
		break;
	}

	return false;
}

void ColliderReact::Render(HDC hDC, float fDeltaTime)
{
	Collider::Render(hDC, fDeltaTime); 
#ifdef _DEBUG

	POSITION CameraPos = Camera::GetInst()->GetPos();

	MoveToEx(hDC, m_tWorldInfo.l- -CameraPos.x, m_tWorldInfo.t - CameraPos.y, nullptr);
	LineTo(hDC, m_tWorldInfo.r -CameraPos.x, m_tWorldInfo.t-CameraPos.y);
	LineTo(hDC, m_tWorldInfo.r -CameraPos.x, m_tWorldInfo.b-CameraPos.y);
	LineTo(hDC, m_tWorldInfo.l -CameraPos.x, m_tWorldInfo.b-CameraPos.y);
	LineTo(hDC, m_tWorldInfo.l -CameraPos.x, m_tWorldInfo.t-CameraPos.y);
#endif // _DEBUG

}

ColliderReact * ColliderReact::Clone()
{
	return new ColliderReact(*this);
}

void ColliderReact::Save(FILE * pFile)
{
	Collider::Save(pFile);
}

void ColliderReact::Load(FILE * pFile)
{
	Collider::Load(pFile);
}



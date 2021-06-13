#include "Bullet.h"
#include "../Resource/Texture.h"
#include "../Collider/ColliderSphere.h"
#include "../Collider/ColliderReact.h"

Bullet::Bullet() : m_fDist(0.f), m_fLimitDist(500.f)
{
}

Bullet::Bullet(const Bullet & bullet) : MoveObject(bullet)
{
	m_fDist = bullet.m_fDist;
	m_fLimitDist = bullet.m_fLimitDist;
}

Bullet::~Bullet()
{
}

bool Bullet::Init()
{
	SetSpeed(400.f);

	SetPivot(0.5f, 0.5);

	SetTexture("Bullet", L"Bullet.bmp");
	m_pTexture->SetColorKey(0, 0, 0);


	ColliderSphere* pSphere = AddCollider<ColliderSphere>("BulletBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 25.f);


	pSphere->Release();
	pSphere = nullptr;
	
	return true;
}

void Bullet::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Bullet::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	MoveAngle(fDeltaTime);

	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fLimitDist)
	{
		Die();
	}

	return 0;
}

int Bullet::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);
	return 0;
}

void Bullet::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void Bullet::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

MoveObject * Bullet::Clone()
{
	return new Bullet(*this);
}

void Bullet::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{

}



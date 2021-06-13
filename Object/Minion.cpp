#include "Minion.h"
#include "../Core.h"
#include "../Collider/ColliderReact.h"
#include "Bullet.h"
#include "../Resource/Texture.h"

Minion::Minion() : m_fFireTime(0.f) ,m_fFireLimit(1.f)
{
}


Minion::Minion(const Minion & minion) : MoveObject(minion)
{
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireLimit = minion.m_fFireLimit;
}


Minion::~Minion()
{
}


bool Minion::Init()
{
	SetPos(600.f, 500.f);
	SetSize(100.f, 100.f);
	SetSpeed(50.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Minion", L"Minion.bmp");
	m_pTexture->SetColorKey(255, 255, 255);


	m_eDir = MD_BACK;

	ColliderReact* pRC = AddCollider<ColliderReact>("MinionBody");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &Minion::CollisionBullet);

	pRC->Release();
	pRC = nullptr;


	return true;
}


void Minion::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}


int Minion::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);


	if (m_tPos.y + m_tSize.y  >= 1200.f )
	{
		m_tPos.y = 1200 - m_tSize.y;
		m_eDir = MD_BACK;
	}

	if (m_tPos.y - 500.f  <= 0.f)
	{
		m_tPos.y = 500.f;
		m_eDir = MD_FRONT;
	}

	MoveYFromSpeed(fDeltaTime, m_eDir);

	m_fFireTime += fDeltaTime;

	if (m_fFireTime >= m_fFireLimit)
	{
		m_fFireTime -= m_fFireLimit;
		Fire();
	}


	return 0;
}

int Minion::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);
	return 0;
}

void Minion::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void Minion::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

	//Ellipse(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y), static_cast<int>(m_tPos.x + m_tSize.x), static_cast<int>(m_tPos.y + m_tSize.y));
}

Minion * Minion::Clone()
{
	return new Minion(*this);
}

void Minion::CollisionBullet(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
}

void Minion::Fire()
{
	/*
	Object* pBullet = Object::CreateCloneObject("Bullet", "MinionBullet", m_pLayer);

 	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (Bullet*)pBullet, &Bullet::Hit);
	
	
	
	((MoveObject*)pBullet)->SetAngle(PI);


	float	x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
	float	y = GetCenter().y;

	pBullet->SetPos(x, y);



	pBullet->Release();
	pBullet = nullptr;
	*/
}


#include "Monster.h"
#include "../Core.h"
#include "Bullet.h"
#include "../Collider/ColliderReact.h"
#include "../Math.h"
#include "../Resource/Texture.h"

Monster::Monster() : m_fFireTime(0.f), m_fFireLimit(2.f)
{

}

Monster::Monster(const Monster& monster) : MoveObject(monster)
{
	m_eDir = monster.m_eDir;
	m_fFireTime = monster.m_fFireTime;
	m_fFireLimit = monster.m_fFireLimit;
}

Monster::~Monster()
{
}

bool Monster::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Monster", L"Monster.bmp");
	m_pTexture->SetColorKey(255, 255, 255);

	m_eDir = MD_FRONT;


	ColliderReact* pTraceRC = AddCollider<ColliderReact>("MonsterTraceRC");

	pTraceRC->SetRect(-300, -300, 300, 300);
	pTraceRC->AddCollisionFunction(CS_STAY, this, &Monster::FollowPlayer);

	pTraceRC->Release();
	pTraceRC = nullptr;


	return true;
}

void Monster::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Monster::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	
	if (m_tPos.y + m_tSize.y >= Core::GetInst()->GetResoulution().iH)
	{
		m_tPos.y = Core::GetInst()->GetResoulution().iH - m_tSize.y;
		m_eDir = MD_BACK;
	}

	if (m_tPos.y <= 0.f)
	{
		m_tPos.y = 0;
		m_eDir = MD_FRONT;
	}

	//MoveYFromSpeed(fDeltaTime, m_eDir);

	m_fFireTime += fDeltaTime;

	if (m_fFireTime >= m_fFireLimit)
	{
		m_fFireTime -= m_fFireLimit;

		Fire();
	}

	return 0;
}

int Monster::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);
	return 0;
}

void Monster::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void Monster::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

	//Ellipse(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y), static_cast<int>(m_tPos.x + m_tSize.x), static_cast<int>(m_tPos.y + m_tSize.y));
}

Monster * Monster::Clone()
{
	return new Monster(*this);
}

void Monster::Fire()
{
	/*
	Object* pBullet = Object::CreateCloneObject("Bullet", "MonsterBullet", m_pLayer);

	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (Bullet*)pBullet, &Bullet::Hit);

	float	x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
	float	y = GetCenter().y;

	pBullet->SetPos(x, y);

	((MoveObject*)pBullet)->SetAngle(PI);
	((Bullet*)pBullet)->SetBulletDistance(1000.f);


	pBullet->Release();
	pBullet = nullptr;
	*/
}

void Monster::FollowPlayer(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if ((pDest->GetTag() == "PlayerBody"))
	{
		 POSITION DestPos = ((ColliderReact*)pDest)->GetObject_()->GetPos();



		 MOVE_DIR eX;
		 MOVE_DIR eY;

		 if (DestPos.x - m_tPos.x < 0)
		 {
			 eX = MD_BACK;
		 }
		 else  eX = MD_FRONT;

		 if (DestPos.y - m_tPos.y < 0)
		 {
			 eY = MD_BACK;
		 }
		 else 	eY = MD_FRONT;


		 MoveXFromSpeed(fDeltaTime * 0.3, eX);
		 MoveYFromSpeed(fDeltaTime * 0.3, eY);
	}
}

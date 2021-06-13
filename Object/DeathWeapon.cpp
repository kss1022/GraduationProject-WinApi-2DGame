#include "DeathWeapon.h"
#include "../Collider/ColliderSphere.h"
#include "../Animation/Animation.h"


DeathWeapon::DeathWeapon()
{
	m_fLifeTime = 0.f;

}

DeathWeapon::DeathWeapon(const DeathWeapon & DeathWeapon) : MoveObject(DeathWeapon)
{
	m_fLifeTime = 0.f;

}

DeathWeapon::~DeathWeapon()
{
}

bool DeathWeapon::Init()
{
	SetSpeed(500.f);


	SetPivot(0.5f, 0.5);
	SetSize(192.f, 192.f);

	ColliderSphere* pSphere = AddCollider<ColliderSphere>("DeathWeaponBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 64.f);


	pSphere->Release();
	pSphere = nullptr;



	Animation* pAnmation = CreateAnimation("DeathWeaponAnimation");


	AddAnimationClip("DeathWeapon", AT_ATLAS, AO_LOPE, 0.2f, 4, 1, 0, 0, 4, 1,
		0.f, "DeathWeapon", L"Enemy/Death/DeathWeapon2.bmp");

	SetAnimationClipColorKey("DeathWeapon", 0, 255, 0);

	m_pAnimation->SetCDefaultClip("DeathWeapon");

	pAnmation->Release();
	pAnmation = nullptr;

	return true;

}

void DeathWeapon::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int DeathWeapon::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	m_fLifeTime += fDeltaTime;
	if (m_fLifeTime >= 3.f)
	{
		Die();
	}

	//	SetAngle(90);

	if (m_tPos.x == m_tPlayerPos.x)
	{
		return 0;
	}

	if (m_tPos.x - m_tPlayerPos.x < 0)
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}
	else 	MoveXFromSpeed(fDeltaTime, MD_BACK);

	if (m_tPos.y - m_tPlayerPos.y< 0)
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	else 	MoveYFromSpeed(fDeltaTime, MD_BACK);


	return 0;
}

int DeathWeapon::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);



	return 0;
}

void DeathWeapon::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void DeathWeapon::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

DeathWeapon * DeathWeapon::Clone()
{
	return new DeathWeapon(*this);
}



void DeathWeapon::SetPlayerPos(const POSITION  tPos)
{
	m_tPlayerPos = tPos;
}

#include "SkeletonBullet.h"
#include "../Collider/ColliderSphere.h"
#include "../Animation/Animation.h"


SkeletonBullet::SkeletonBullet()
{
}

SkeletonBullet::SkeletonBullet(const SkeletonBullet & bullet) : MoveObject(bullet)
{
}

SkeletonBullet::~SkeletonBullet()
{
}

bool SkeletonBullet::Init()
{
	SetSpeed(150.f);


	SetPivot(0.5f, 0.5);
	SetSize(100.f, 100.f);
	
	SetPhysics(true);
	SetForce(300.f);


	//SetTexture("Bullet", L"Bullet.bmp");
	//m_pTexture->SetColorKey(0, 0, 0);


	ColliderSphere* pSphere = AddCollider<ColliderSphere>("SkeletonBulletBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 25.f);


	pSphere->Release();
	pSphere = nullptr;



	Animation* pAnmation = CreateAnimation("SkeletonBulletAnimation");


	AddAnimationClip("SkeletonBullet", AT_ATLAS, AO_LOPE, 1.f, 4, 1, 0, 0, 4, 1,
		0.f, "SkeletonBullet", L"Enemy/Skeleton/SkeletonBullet.bmp");

	SetAnimationClipColorKey("SkeletonBullet", 255, 255, 255);

	m_pAnimation->SetCDefaultClip("SkeletonBullet");

	pAnmation->Release();
	pAnmation = nullptr;

	return true;

}

void SkeletonBullet::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int SkeletonBullet::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	//MoveAngle(fDeltaTime);

	MoveXFromSpeed(fDeltaTime, MD_BACK);
	Jump(fDeltaTime);

	if (m_tPos.y >= 700)
	{
		Die();
	}

	return 0;
}

int SkeletonBullet::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);
	return 0;
}

void SkeletonBullet::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void SkeletonBullet::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

SkeletonBullet * SkeletonBullet::Clone()
{
	return new SkeletonBullet(*this);
}

void SkeletonBullet::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	
}

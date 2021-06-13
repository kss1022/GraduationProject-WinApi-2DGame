#include "Skeleton.h"
#include "../Collider/ColliderReact.h"
#include "../Animation/Animation.h"
#include "SkeletonBullet.h"
#include "../Scene/Scene.h"
#include "../Collider/Collider.h"
#include "../Sound/SoundManager.h"

Skeleton::Skeleton()
{
	m_bStay = false;
	m_bAttack = false;
	m_fAttackTime = 0.f;

	m_bDie = false;
	m_fDieTime = 0.f;
}

Skeleton::Skeleton(const Skeleton & Skeleton) : MoveObject(Skeleton)
{
	m_bStay = false;
	m_bAttack = false;
	m_fAttackTime = 0.f;

	m_bDie = false;
	m_fDieTime = 0.f;
}

Skeleton::~Skeleton()
{
}


bool Skeleton::Init()
{
	SetPos(1700.f, 640.f);
	SetSize(200, 200.0f);
	SetSpeed(150.f);
	SetPivot(0.5f, 0.5f);
	//SetImageOffset(8.f, 8.f);




	ColliderReact* pReact = AddCollider<ColliderReact>("SkeletonBody");


	pReact->SetRect(-28, -40, 28, 40);
	pReact->AddCollisionFunction(CS_ENTER, this, &Skeleton::Hit);


	pReact->Release();
	pReact = nullptr;



	ColliderReact* pReact2 = AddCollider<ColliderReact>("SkeletonRange");


	pReact2->SetRect(-100, -50, 100, 50);
	pReact2->SetCollierOffset(-150.f, -15.f);


	pReact2->AddCollisionFunction(CS_ENTER, this, &Skeleton::Hit);
	pReact2->AddCollisionFunction(CS_STAY, this, &Skeleton::Stay);
	pReact2->AddCollisionFunction(CS_LEAVE, this, &Skeleton::Leave);

	pReact2->Release();
	pReact2 = nullptr;


	Animation* pAnmation = CreateAnimation("SkeletonAnimation");


	AddAnimationClip("SkeletonNone", AT_ATLAS, AO_LOPE, 2.f, 6, 1, 0, 0, 6, 1,
		0.f, "SkeletonNone", L"Enemy/Skeleton/SkeletonMove.bmp");
	SetAnimationClipColorKey("SkeletonNone", 255, 255, 255);


	AddAnimationClip("SkeletonMove", AT_ATLAS, AO_LOPE, 2.f, 6, 1, 0, 0, 6, 1,
		0.f, "SkeletonMove", L"Enemy/Skeleton/SkeletonMove.bmp");

	SetAnimationClipColorKey("SkeletonMove", 255, 255, 255);



	AddAnimationClip("SkeletonFight", AT_ATLAS, AO_ONCE_RETURN, 1.f, 6, 1, 0, 0, 6, 1,
		0.f, "SkeletonFight", L"Enemy/Skeleton/SkeletonAttack.bmp");
	SetAnimationClipColorKey("SkeletonFight", 255, 255, 255);


	AddAnimationClip("SkeletonDie", AT_ATLAS, AO_ONCE_RETURN, 2.f, 6, 1, 0, 0, 6, 1,
		0.f, "SkeletonDie", L"Enemy/Skeleton/SkeletonDie.bmp");
	SetAnimationClipColorKey("SkeletonDie", 255, 255, 255);



	m_pAnimation->SetCDefaultClip("SkeletonNone");

	pAnmation->Release();
	pAnmation = nullptr;


	return true;
}

void Skeleton::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);
}

int Skeleton::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);


	//공격 받앗을시 공격 모션이 종료되면 사망
	if (m_bDie)
	{
		SetSpeed(0.f);

		m_fDieTime += fDeltaTime;


		if (m_fDieTime >= 0.5f)
		{
			Die();
			m_pScene->GoldUp(100);
			SoundManager::GetInst()->LoadSound("SkeletonDie", false, "SkeletonDie.wav");
			SoundManager::GetInst()->Play("SkeletonDie");
		}
	}




	if (m_bStay)
	{
		m_fAttackTime += fDeltaTime;
		SetSpeed(0.f);


		if (m_fAttackTime >= 1.f)
		{
			m_pAnimation->ChangeClip("SkeletonFight");
		}


		if (m_fAttackTime >= 2.f)
		{
			m_fAttackTime -= 2.f;
			Fire();
		}
	}


	MoveXFromSpeed(fDeltaTime, MD_BACK);
	SetSpeed(150.f);


	




	return 0;
}

int Skeleton::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);


	if (m_tPos.x <= 45.f)
	{
		m_pScene->GameOver(fDeltaTime);
	}

	return 0;
}

void Skeleton::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void Skeleton::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

Skeleton * Skeleton::Clone()
{
	return new Skeleton(*this);
}




void Skeleton::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{

	//플레이어를 만났을시 멈추고 기본 모션을 가만히 함
	if (pDest->GetTag() == "PlayerBody" || pDest->GetTag() == "DraculaBody" || pDest->GetTag() == "HorseBody")
	{
		Skeleton* pSkeleton = (Skeleton*)pSrc->GetObject_();
		pSkeleton->m_pAnimation->SetCDefaultClip("SkeletonNone");
	}
	
	
	//공격당함
	if ( pSrc->GetTag() == "SkeletonBody" &&  (pDest->GetTag() == "WeaponBody"   ||
		pDest->GetTag() == "Skill1Range"  ||    pDest->GetTag() == "SkillRange" ||
		pDest->GetTag() == "DraculaSkillBody" || pDest->GetTag() == "HorseBody"    )
		)
	{
		Skeleton* pSkeleton = (Skeleton*)pSrc->GetObject_();

		pSkeleton->m_bDie = true;

		pSkeleton->m_pAnimation->ChangeClip("SkeletonDie");


		SoundManager::GetInst()->LoadSound("Enemy hit", false, "Enemy hit.wav");
		SoundManager::GetInst()->Play("Enemy hit");
	}


}

void Skeleton::Stay(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	Skeleton* pSkeleton = (Skeleton*)pSrc->GetObject_();

	if (pSkeleton->GetDie())
	{
		return;
	}


	if (pDest->GetTag() == "PlayerBody" || pDest->GetTag() == "DraculaBody" || pDest->GetTag() == "HorseBody")
	{
		pSkeleton->m_bStay = true;
	}
}

void Skeleton::Leave(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	Skeleton* pSkeleton = (Skeleton*)pSrc->GetObject_();

	if (pSkeleton->GetDie())
	{
		return;
	}



	if (pDest->GetTag() == "PlayerBody" || pDest->GetTag() == "DraculaBody" || pDest->GetTag() == "HorseBody")
	{
		pSkeleton->m_pAnimation->SetCDefaultClip("SkeletonMove");
		pSkeleton->m_pAnimation->ChangeClip("SkeletonMove");
		pSkeleton->m_bStay = false;
	}
}





void Skeleton::Fire(Collider * pSrc)
{
	Object* pBullet = Object::CreateCloneObject("SkeletonBullet", "SkeletonBullet", pSrc->GetObject_()->GetScene()
		->GetSceneType(), pSrc->GetObject_()->GetLayer());

	pBullet->m_pAnimation->SetObject(pBullet);


	pBullet->AddCollisionFunction("SkeletonBulletBody", CS_ENTER,
		(SkeletonBullet*)pBullet, &SkeletonBullet::Hit);




	((MoveObject*)pBullet)->SetAngle(PI);

	float	x = pSrc->GetObject_()->GetCenter().x;
	float	y = pSrc->GetObject_()->GetCenter().y - 40;

	pBullet->SetPos(x, y);

	((MoveObject*)pBullet)->ClearGravity();
	((MoveObject*)pBullet)->JumpEnd();



	pBullet->Release();
	pBullet = nullptr;
}


void Skeleton::Fire()
{
	Object* pBullet = Object::CreateCloneObject("SkeletonBullet", "SkeletonBullet", m_pScene->GetSceneType(), m_pLayer);

	pBullet->m_pAnimation->SetObject(pBullet);


	pBullet->AddCollisionFunction("SkeletonBulletBody", CS_ENTER,
		(SkeletonBullet*)pBullet, &SkeletonBullet::Hit);




	((MoveObject*)pBullet)->SetAngle(PI);

	float	x = GetCenter().x;
	float	y = GetCenter().y - 40;

	pBullet->SetPos(x, y);

	((MoveObject*)pBullet)->ClearGravity();
	((MoveObject*)pBullet)->JumpEnd();


	pBullet->Release();
	pBullet = nullptr;
}


bool Skeleton::GetDie() const
{
	return m_bDie;
}



/*

void Skeleton::Fire()
{
	Object* pBullet = Object::CreateCloneObject("SkeletonBullet", "SkeletonBullet", SC_CURRENT, m_pLayer);
	pBullet->m_pAnimation->SetObject(pBullet);


	pBullet->AddCollisionFunction("SkeletonBulletBody", CS_ENTER,
		(SkeletonBullet*)pBullet, &SkeletonBullet::Hit);




	((MoveObject*)pBullet)->SetAngle(PI);

	float	x = GetCenter().x;
	float	y = GetCenter().y - 40;

	pBullet->SetPos(x, y);

	((MoveObject*)pBullet)->ClearGravity();
	((MoveObject*)pBullet)->JumpEnd();



	pBullet->Release();
	pBullet = nullptr;
}
*/
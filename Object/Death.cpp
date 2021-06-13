#include "Death.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderReact.h"
#include "../Scene/Scene.h"
#include "../Core/Input.h"
#include "Player.h"
#include "DeathWeapon.h"
#include "../Math.h"


#include "../Sound/SoundManager.h"
Death::Death()
{
	m_pObject = nullptr;
	m_iHP = 1500;
	m_bMoveAttack = false;
	m_fAttackTime = 0.f;
	m_bMotion = false;
	m_fSkillTime = 0.f;
	m_bDie = false;
}

Death::Death(const Death & Death) : MoveObject(Death)
{
	m_iHP = 1500;
	m_bMoveAttack = false;
	m_fAttackTime = 0.f;
	m_bMotion = false;
	m_fSkillTime = 0.f;
	m_bDie = false;
}

Death::~Death()
{
	if (m_WeaponBody)
	{
		m_WeaponBody->Release();
		m_WeaponBody = nullptr;
	}
}

bool Death::Init()
{
	SetPos(750.f, 100.f);
	SetSize(200, 200.0f);
	SetSpeed(50.f);
	SetPivot(0.5f, 0.5f);




	ColliderReact* pReact = AddCollider<ColliderReact>("DeathBody");


	pReact->SetRect(-25, -50, 25, 50);
	pReact->SetCollierOffset(0, 30.f);
	pReact->AddCollisionFunction(CS_ENTER, this, &Death::Hit);


	pReact->Release();
	pReact = nullptr;

	Animation* pAnmation = CreateAnimation("DeathAnimation");


	AddAnimationClip("DeathMoveLeft", AT_ATLAS, AO_LOPE, 2.f, 4, 1, 0, 0, 4, 1,
		0.f, "DeathMoveLeft", L"Enemy/Death/MoveLeft.bmp");
	SetAnimationClipColorKey("DeathMoveLeft", 0, 255, 0);


	AddAnimationClip("DeathMoveRight", AT_ATLAS, AO_LOPE, 2.f, 4, 1, 0, 0, 4, 1,
		0.f, "DeathMoveRight", L"Enemy/Death/MoveRight.bmp");
	SetAnimationClipColorKey("DeathMoveRight", 0, 255, 0);




	AddAnimationClip("DeathWarp", AT_ATLAS, AO_LOPE, 0.5f, 4, 1, 0, 0, 4, 1,
		0.f, "DeathWarp", L"Enemy/Death/Warp.bmp");
	SetAnimationClipColorKey("DeathWarp", 0, 255, 0);


	AddAnimationClip("DeathDownAttack", AT_ATLAS, AO_LOPE, 0.5f, 5, 1, 0, 0, 5, 1,
		0.f, "DeathDownAttack", L"Enemy/Death/DeathDownAttack.bmp");
	SetAnimationClipColorKey("DeathDownAttack", 0, 255, 0);


	AddAnimationClip("DeathThrowWeapon", AT_ATLAS, AO_LOPE, 3.f, 5, 1, 0, 0, 5, 1,
		0.f, "DeathThrowWeapon", L"Enemy/Death/ThrowWeapon.bmp");
	SetAnimationClipColorKey("DeathThrowWeapon", 0, 255, 0);



	AddAnimationClip("DeathAttackLeft", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 6, 1, 0, 0, 6, 1,
		0.f, "DeathAttackLeft", L"Enemy/Death/AttackLeft.bmp");
	SetAnimationClipColorKey("DeathAttackLeft", 0, 255, 0);



	AddAnimationClip("DeathAttackRight", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 6, 1, 0, 0, 6, 1,
		0.f, "DeathAttackRight", L"Enemy/Death/AttackRight.bmp");
	SetAnimationClipColorKey("DeathAttackRight", 0, 255, 0);


	AddAnimationClip("DeathHit", AT_ATLAS, AO_ONCE_RETURN, 2.f, 2, 1, 0, 0, 2, 1,
		0.f, "DeathHit", L"Enemy/Death/DeathHit.bmp");
	SetAnimationClipColorKey("DeathHit", 0, 255, 0);

	AddAnimationClip("DeathDie", AT_ATLAS, AO_LOPE, 2.f, 3, 1, 0, 0, 3, 1,
		0.f, "DeathDie", L"Enemy/Death/DeathDie.bmp");
	SetAnimationClipColorKey("DeathDie", 0, 255, 0);


	m_pAnimation->SetCDefaultClip("DeathMoveLeft");

	pAnmation->Release();
	pAnmation = nullptr;

	return true;
}

void Death::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);

}

int Death::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);

	//움직임
	m_tDistance.x = m_tPos.x - m_pObject->GetPos().x;
	m_tDistance.y = m_tPos.y - m_pObject->GetPos().y;

	if (m_tDistance.x > 0)
	{
		m_eX = MD_BACK;
		m_pAnimation->SetCDefaultClip("DeathMoveLeft");

		if (!m_bMotion)
		{
			m_pAnimation->ChangeClip("DeathMoveLeft");
		}
	}
	else
	{
		m_eX = MD_FRONT;
		m_pAnimation->SetCDefaultClip("DeathMoveRight");

		if (!m_bMotion)
		{
			m_pAnimation->ChangeClip("DeathMoveRight");
		}
	}

	if (m_tDistance.y > 0)
	{
		m_eY = MD_BACK;
	}
	else m_eY = MD_FRONT;




	MoveXFromSpeed(fDeltaTime, m_eX);
	MoveYFromSpeed(fDeltaTime, m_eY);


	if (!m_bDie)
	{
		m_fSkillTime += fDeltaTime;


		if (m_fSkillTime > 1.f)
		{
			if (rand() % 2000 == 1)
			{
				Warp();
				m_fSkillTime = 0.f;
			}


			if (m_fSkillTime > 3.f)
			{
				if (rand() % 1000 == 1)
				{
					MoveAttack();
					m_fSkillTime = 0.f;
				}

				if (m_fSkillTime > 6.f)
				{
					DownAttack();
					m_fSkillTime = 0.f;
				}
			}
		}

	}



	return 0;
}

int Death::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);

	//MoveAttack인경우 이동하면서 떄림
	if (m_bMoveAttack)
	{
		m_fAttackTime += fDeltaTime;
		MoveX(m_eX * 100, fDeltaTime * 5);

		if (m_fAttackTime >= 0.5)
		{
			m_fAttackTime = 0.f;
			m_bMoveAttack = false;
		}
	}



	//모션발동 && 에니메이션의 모션이 끝남->모션이 끝남
	if (m_bMotion && m_pAnimation->GetMotionEnd())
	{
		if (m_pAnimation->GetCurrentStrClip() == "DeathWarp")
		{
			ThrowWeapon();
		}

		if (m_pAnimation->GetCurrentStrClip() == "DeathDie")
		{
			Die();

		}


		else
		{
			m_bMotion = false;
			m_pAnimation->ReturenClip();
		}

		if (m_WeaponBody)
		{
			list<Collider*>::iterator iter;
			list<Collider*>::iterator iterEnd = m_ColliderList.end();

			for (iter = m_ColliderList.begin(); iter != iterEnd;)
			{
				if ((*iter)->GetTag() == m_WeaponBody->GetTag())
				{
					iter = m_ColliderList.erase(iter);

				}
				else iter++;
			}


			m_WeaponBody->Release();
			m_WeaponBody = nullptr;
		}
	}



	return 0;
}

void Death::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void Death::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);
}

Death * Death::Clone()
{
	return new Death(*this);
}







Object * Death::GetObject_() const
{
	return m_pObject;
}

void Death::SetObject(Object * obj)
{
	m_pObject = obj;
}

void Death::Warp()
{
	m_pAnimation->ChangeClip("DeathWarp");

	m_tPos.x = rand() % 1500 + 300;
	m_tPos.y = rand() % 500 + 100;

	m_bMotion = true;
}

void Death::DownAttack()
{
	m_tPos = m_pObject->GetPos();

	m_tPos.x -= 10.f;
	m_tPos.y -= 120.f;

	m_WeaponBody = AddCollider<ColliderReact>("DeathAttack");
	m_WeaponBody->SetRect(-10.f, -28.f, 10.f, 28.f);
	m_WeaponBody->SetCollierOffset(10.f, 65.f);
	m_WeaponBody->Release();


	m_pAnimation->ChangeClip("DeathDownAttack");

	m_bMotion = true;
}

void Death::MoveAttack()
{
	m_WeaponBody = AddCollider<ColliderReact>("DeathAttack");
	m_WeaponBody->SetRect(-25.f, -60.f, 25.f, 60.f);


	if (m_eX == 1)
	{
		m_pAnimation->ChangeClip("DeathAttackRight");
		m_WeaponBody->SetCollierOffset(50.f, 20.f);
	}
	else
	{
		m_pAnimation->ChangeClip("DeathAttackLeft");
		m_WeaponBody->SetCollierOffset(-50.f, 20.f);
	}




	m_WeaponBody->Release();

	m_bMoveAttack = true;


	m_bMotion = true;
}

void Death::ThrowWeapon()
{
	Object* pWeapon = Object::CreateCloneObject("DeathWeapon", "DeathWeapon", SC_CURRENT, m_pLayer);

	pWeapon->m_pAnimation->SetObject(pWeapon);


	((DeathWeapon*)pWeapon)->SetPlayerPos(m_pObject->GetPos());
	pWeapon->SetPos(m_tPos.x + m_eX * 30, m_tPos.y + m_eY * 10);



	m_pAnimation->ChangeClip("DeathThrowWeapon");
	m_bMotion = true;


	pWeapon->Release();
	pWeapon = nullptr;
}

void Death::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if (pSrc->GetTag() == "DeathBody" && (pDest->GetTag() == "WeaponBody" ||
		pDest->GetTag() == "Skill1Range" || pDest->GetTag() == "SkillRange" ||
		pDest->GetTag() == "DraculaSkillBody" || pDest->GetTag() == "HorseBody")
		)
	{
		Death* pDeath = (Death*)pSrc->GetObject_();

		pDeath->m_iHP -= 100;

		pDeath->m_pAnimation->ChangeClip("DeathHit");
		pDeath->m_bMotion = true;


		if (pDeath->m_iHP <= 0)
		{
			pDeath->m_pAnimation->ChangeClip("DeathDie");
			m_bDie = true;
		}

		SoundManager::GetInst()->LoadSound("Enemy hit", false, "Enemy hit.wav");
		SoundManager::GetInst()->Play("Enemy hit");
	}
}

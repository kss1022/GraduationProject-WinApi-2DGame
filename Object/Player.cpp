#include "Player.h"
#include "../Core/Input.h"
#include "Bullet.h"
#include "../Collider/ColliderReact.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"
#include "../Sound/SoundManager.h"




#include "HPBar.h"
#include "Skill1.h"
#include "Skill2.h"

Player::Player()
{
}

Player::Player(const Player & player) : MoveObject(player)
{

}

Player::~Player()
{
	if (m_WeaponBody)
	{
		m_WeaponBody->Release();
		m_WeaponBody = nullptr;
	}

}

bool Player::Init()
{
	SetPos(200.f, 500.f);
	SetSize(200.f, 86.f);
	SetSpeed(300.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 50.f);
	//	SetTexture("Player", L"HOS.bmp");


	ColliderReact* pBody = AddCollider<ColliderReact>("PlayerBody");

	pBody->SetRect(-16.f, -43.f, 16.f, 43.f);
	pBody->SetCollierOffset(-5.f, 0.f);
	pBody->AddCollisionFunction(CS_ENTER, this, &Player::Hit);
	pBody->AddCollisionFunction(CS_STAY, this, &Player::HitStay);


	pBody->Release();
	pBody = nullptr;


	ColliderReact* pBottom = AddCollider<ColliderReact>("PlayerBottom");

	pBottom->AddCollisionFunction(CS_ENTER, this, &Player::Hit);
	pBottom->AddCollisionFunction(CS_STAY, this, &Player::HitStay);
	pBottom->SetRect(-16.f, -5.f, 16.f, 5.f);
	pBottom->SetCollierOffset(-5.f, 35.f);

	pBottom->Release();
	pBottom = nullptr;


	m_iHP = 1500;
	m_iMP = 1500;
	m_iDir = 0;
	//중력을 적용한다.


	SetPhysics(true);

	//점프할 힘을 설정한다.
	SetForce(300.f);


	m_bFrontDash = false;
	m_bBackDash = false;
	m_fDashTime = 0.f;

	m_bDemage = false;
	m_fDemageTime = 0.f;

	m_bSkill = false;
	m_fSkillTime = 0.f;
	m_iSkillNumber = 0;

	Animation* pAnimation = CreateAnimation("PlayerAnimation");


	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOPE, 1.f, 6, 1, 0, 0, 6, 1,
		0.f, "PlayerIdleRight", L"Player/Idle/Right/StandRight.bmp");
	//m_pTexture->SetColorKey(0, 128, 255);  //SetColorKey(0, 128, 255);

	SetAnimationClipColorKey("IdleRight", 0, 0, 0);


	AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOPE, 1.f, 6, 1, 0, 0, 6, 1,
		0.f, "PlayerIdleLeft", L"Player/Idle/Left/StandLeft.bmp");

	SetAnimationClipColorKey("IdleLeft", 0, 0, 0);



	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 1.f, 7, 1, 0, 0, 7, 1,
		0.f, "PlayerRunRight", L"Player/Idle/Right/RunRight.bmp");

	SetAnimationClipColorKey("RunRight", 0, 0, 0);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 1.f, 7, 1, 0, 0, 7, 1,
		0.f, "PlayerRunLeft", L"Player/Idle/Left/RunLeft.bmp");

	SetAnimationClipColorKey("RunLeft", 0, 0, 0);

	AddAnimationClip("AttackRight", AT_ATLAS, AO_ONCE_RETURN, 0.3f, 6, 1, 0, 0, 6, 1,
		0.f, "PlayerAttackRight", L"Player/Idle/Right/AttackRight.bmp");

	SetAnimationClipColorKey("AttackRight", 0, 0, 0);

	AddAnimationClip("AttackLeft", AT_ATLAS, AO_ONCE_RETURN, 0.3f, 6, 1, 0, 0, 6, 1,
		0.f, "PlayerAttackLeft", L"Player/Idle/Left/AttackLeft.bmp");

	SetAnimationClipColorKey("AttackLeft", 0, 0, 0);





	AddAnimationClip("JumpRight", AT_ATLAS, AO_ONCE_RETURN, 0.7f, 7, 1, 0, 0, 7, 1,
		0.f, "JumpRight", L"Player/Idle/Right/JumpRight.bmp");

	SetAnimationClipColorKey("JumpRight", 0, 0, 0);

	AddAnimationClip("JumpLeft", AT_ATLAS, AO_ONCE_RETURN, 0.7f, 7, 1, 0, 0, 7, 1,
		0.f, "JumpLeft", L"Player/Idle/Left/JumpLeft.bmp");

	SetAnimationClipColorKey("JumpLeft", 0, 0, 0);


	AddAnimationClip("Dash", AT_ATLAS, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1,
		0.f, "Dash", L"Player/Idle/Dash.bmp");

	SetAnimationClipColorKey("Dash", 0, 0, 0);

	AddAnimationClip("DashBack", AT_ATLAS, AO_ONCE_RETURN, 0.3f, 3, 1, 0, 0, 3, 1,
		0.f, "DashBack", L"Player/Idle/DashBack.bmp");

	SetAnimationClipColorKey("DashBack", 0, 0, 0);



	AddAnimationClip("SkillMotion", AT_ATLAS, AO_ONCE_RETURN, 1.2f, 8, 1, 0, 0, 8, 1,
		0.f, "SkillMotion", L"Player/Idle/Attack/SkillMotion.bmp");

	SetAnimationClipColorKey("SkillMotion", 0, 0, 0);


	AddAnimationClip("Hit", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 4, 1, 0, 0, 4, 1,
		0.f, "Hit", L"Player/Idle/Hit.bmp");

	SetAnimationClipColorKey("Hit", 0, 0, 0);

	AddAnimationClip("JumpHit", AT_ATLAS, AO_ONCE_RETURN, 1.f, 8, 1, 0, 0, 8, 1,
		0.f, "JumpHit", L"Player/Idle/JumpHit.bmp");

	SetAnimationClipColorKey("JumpHit", 0, 0, 0);





	/*
	vector<wstring> vecFileName;
	vecFileName.reserve(14);

	for (int i = 1; i <= 14; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Idle/Attack/Boom%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("PlayerBoom", AT_FRAME, AO_ONCE_RETURN, 1.f, 14, 1, 0, 0, 14, 1,
		0.f, "PlayerBoom", vecFileName);
	SetAnimationClipColorKey("PlayerBoom", 128, 128, 255);
	*/




	pAnimation->Release();
	pAnimation = nullptr;




	return true;
}

void Player::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);


	//움직임
	if (KEYPRESS("MoveLeft") )
	{
		if(m_tPos.x >= 50) MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_bMove = true;

		if (!m_bMotion)
		{
			m_pAnimation->ChangeClip("RunLeft");
		}
		m_iDir = -1;
		m_pAnimation->SetCDefaultClip("IdleLeft");
	}

	if (KEYPRESS("MoveRight"))
	{
		if (m_tPos.x <= 1800) MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_bMove = true;

		if (!m_bMotion)
		{
			m_pAnimation->ChangeClip("RunRight");
		}
		m_iDir = 1;
		m_pAnimation->SetCDefaultClip("IdleRight");
	}



	if (KEYDOWN("Attack"))
	{
		if (!m_WeaponBody)
		{
			Attack();
		}
	}



	if (!m_bJump)
	{
		if (KEYPRESS("Jump"))
		{

			SoundManager::GetInst()->LoadSound("Jump", false, "Jump.wav");

			SoundManager::GetInst()->Volume(ST_EFFECT, 0.1f);

			SoundManager::GetInst()->Play("Jump");


			Jump(fDeltaTime);


			if (!m_bMotion)
			{
				if (m_iDir == -1)
					m_pAnimation->ChangeClip("JumpLeft");
				else
					m_pAnimation->ChangeClip("JumpRight");
				m_bMotion = true;
			}
		}
	}

	if (m_bJump && m_fJumpTime >= 0.002f)
	{
		if (KEYDOWN("Jump"))
		{
			SoundManager::GetInst()->LoadSound("Jump2", false, "Jump2.wav");
			SoundManager::GetInst()->Play("Jump2");

			DoubleJump();

			if (m_iDir == -1)
				m_pAnimation->ChangeClip("JumpLeft");
			else
				m_pAnimation->ChangeClip("JumpRight");
		}

		m_bMotion = true;
	}


	if (KEYDOWN("KeyPadQ"))
	{
		BackDash();
	}


	if (KEYDOWN("KeyPadE"))
	{
		FrontDash();
	}


	if (KEYDOWN("Skill1"))
	{
		if (m_iMP >= 1400)
		{
			SkillMotion();
			m_iSkillNumber = 1;
			m_iMP -= 1400;
		}
	}


	if (KEYDOWN("Skill2"))
	{
		if (m_iMP >= 700)
		{
			SkillMotion();
			m_iSkillNumber = 2;
			m_iMP -= 700;
		}
	}

	/*
	if (KEYPRESS("MoveFront"))
	{
		MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYPRESS("MoveBack"))
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	*/
}

int Player::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);




	//모션발동 && 에니메이션의 모션이 끝남->모션이 끝남
	if (m_bMotion && m_pAnimation->GetMotionEnd())
	{
		m_bMotion = false;


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

	//움직이지 않는 상태 && 모션이 끝난경우 DefaultClip으로 변경
	if (!m_bMove && !m_bMotion)
	{
		m_pAnimation->ReturenClip();
	}

	if (m_iMP < 1500)
	{
		m_iMP += 1;
	}


	return 0;
}

int Player::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);


	if (m_bSkill)
	{
		SetPhysics(false);

		m_fSkillTime += fDeltaTime;

		if (m_fSkillTime <= 0.3f)
		{
			if (!m_bJump)
			{
				MoveYFromSpeed(fDeltaTime, MD_BACK);
			}
		}


		if (m_fSkillTime >= 0.5f)
		{
			switch (m_iSkillNumber)
			{
			case 1:
				Skill1();
				break;
			case 2:
				Skill_2();
				break;
			default:
				break;
			}



			SetPhysics(true);
			m_bSkill = false;
			m_fSkillTime = 0.f;

		}

	}


	if (m_bFrontDash)
	{
		m_fDashTime += fDeltaTime;
		if (m_fDashTime >= 0.2f)
		{
			m_bFrontDash = false;
			m_fDashTime = 0.f;
		}

		if (m_tPos.x <= 1800) MoveXFromSpeed(fDeltaTime * 2, MD_FRONT);
	}



	if (m_bBackDash)
	{
		m_fDashTime += fDeltaTime;
		if (m_fDashTime >= 0.2f)
		{
			m_bBackDash = false;
			m_fDashTime = 0.f;
		}
		if (m_tPos.x >= 50) MoveXFromSpeed(fDeltaTime * 2, MD_BACK);
	}



	if (m_bDemage)
	{
		m_fDemageTime += fDeltaTime;

		if (m_fDemageTime >= 0.5f)
		{
			m_bDemage = false;
			m_fDemageTime = 0.f;
		}
		 MoveXFromSpeed(fDeltaTime, MD_BACK);
	}


	return 0;
}

void Player::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);
}

void Player::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

	/*
	wchar_t strHP[32] = {};

	wsprintf(strHP, L"HP  : %d", m_iHP);


	POSITION	tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= Camera::GetInst()->GetPos();



	TextOut(hDC, tPos.x, tPos.y - 20, strHP, lstrlen(strHP));
	*/
}

Player * Player::Clone()
{
	return new Player(*this);
}



void Player::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	//	if (pDest->GetTag() == "MonsterTraceRC") return;

	if (pDest->GetTag() == "SkeletonBody" || pDest->GetTag() == "SkeletonBulletBody" ||
		pDest->GetTag() == "DeathBody" || pDest->GetTag() == "DeathAttack" ||
		pDest->GetTag() == "DeathWeaponBody" || pDest->GetTag() == "CreatureSkill" ||
		pDest->GetTag() == "CreatureBody"	|| pDest->GetTag() == "MummyBody"
		)
	{
		if (!m_bDemage)
		{
			Demage(100);
		}
	}

	if (m_iHP <= 0)
	{
		Die();
	}

	if (pDest->GetTag() == "StageColl" && pSrc->GetTag() == "PlayerBottom")
	{
		ClearGravity();
		JumpEnd();

		//m_tPos.y = pSrc->GetHitPoint().y - (m_tPivot.y * m_tSize.y);


		m_tPos.y--;
	}
}

void Player::HitStay(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "StageColl" && pSrc->GetTag() == "PlayerBottom")
	{
		ClearGravity();
		JumpEnd();
		//m_tPos.y = pSrc->GetHitPoint().y - (m_tPivot.y * m_tSize.y);

		m_tPos.y--;
	}
}


int Player::GetHP() const
{
	return m_iHP;
}

int Player::GetMP() const
{
	return m_iMP;
}









void Player::Attack()
{
	SoundManager::GetInst()->LoadSound("Attack", false, "Attack.wav");
	SoundManager::GetInst()->Play("Attack");


	m_bMotion = true;

	m_WeaponBody = AddCollider<ColliderReact>("WeaponBody");

	m_WeaponBody->SetRect(-26.f, -6.f, 26.f, 6.f);

	if (m_iDir == 1)
	{
		m_WeaponBody->SetCollierOffset(70.f, -10.f);
	}
	else
	{
		m_WeaponBody->SetCollierOffset(-70.f, -10.f);
	}
	m_WeaponBody->Release();




	if (m_iDir == -1)
		m_pAnimation->ChangeClip("AttackLeft");
	else
		m_pAnimation->ChangeClip("AttackRight");
}

void Player::SkillMotion()
{
	SoundManager::GetInst()->LoadSound("MeTho", false, "MeTho.wav");
	SoundManager::GetInst()->Play("MeTho");
	SoundManager::GetInst()->Volume(ST_EFFECT, 0.7f);


	m_pAnimation->ChangeClip("SkillMotion");
	m_bSkill = true;
	m_bMotion = true;
}

void Player::Skill1()
{
	SoundManager::GetInst()->LoadSound("Skill1", false, "Skill1.wav");
	SoundManager::GetInst()->Play("Skill1");
	SoundManager::GetInst()->Volume(ST_EFFECT, 0.3f);
	//스킬효과

	int	iPosY = m_tPos.y - 40;


	for (int i = m_tPos.x - 30; i >= 100; i -= 60)
	{
		Object* pSkill1 = Object::CreateCloneObject("Skill1Protocal", "Skll1", m_pScene->GetSceneType(), m_pLayer);

		if (iPosY <= 600)
		{
			iPosY += 40;

		}
		pSkill1->SetPos(i, iPosY);

		pSkill1->Release();
		pSkill1 = nullptr;
	}



	iPosY = m_tPos.y - 40;
	for (int i = m_tPos.x + 30; i <= 1800; i += 60)
	{
		Object* pSkill1 = Object::CreateCloneObject("Skill1Protocal", "Skll1", m_pScene->GetSceneType(), m_pLayer);

		if (iPosY <= 600)
		{
			iPosY += 40;

		}
		pSkill1->SetPos(i, iPosY);

		pSkill1->Release();
		pSkill1 = nullptr;
	}

}

void Player::Skill_2()
{
	Object* pSkill2 = Object::CreateCloneObject("Skill2Protocal", "Skill2", m_pScene->GetSceneType(), m_pLayer);


	pSkill2->SetPos(m_tPos.x - 50.f, 100.f);



	pSkill2->Release();
	pSkill2 = nullptr;
}

void Player::FrontDash()
{
	SoundManager::GetInst()->LoadSound("Dash", false, "Dash.wav");
	SoundManager::GetInst()->Play("Dash");
	SoundManager::GetInst()->Volume(ST_EFFECT, 0.3f);

	m_bFrontDash = true;

	m_pAnimation->ChangeClip("Dash");
	m_bMotion = true;
}

void Player::BackDash()
{
	SoundManager::GetInst()->LoadSound("Dash", false, "Dash.wav");
	SoundManager::GetInst()->Play("Dash");
	SoundManager::GetInst()->Volume(ST_EFFECT, 0.3f);

	m_bBackDash = true;

	m_pAnimation->ChangeClip("DashBack");
	m_bMotion = true;
}

void Player::Demage(int iDemage)
{
	SoundManager::GetInst()->LoadSound("Uckk", false, "Uckk.wav");
	SoundManager::GetInst()->Play("Uckk");
	//SoundManager::GetInst()->Volume(ST_EFFECT, 0.5f);



	m_iHP -= iDemage;

	m_bMotion = true;
	m_bDemage = true;


	if (m_bJump)
	{
		m_pAnimation->ChangeClip("JumpHit");
	}
	else
		m_pAnimation->ChangeClip("Hit");
}












/*
void Player::Fire()
{

	m_bMotion = true;

	Object* pBullet = Object::CreateCloneObject("Bullet", "PlayerBullet", m_pScene->GetSceneType(), m_pLayer);

	pBullet->AddCollisionFunction("BulletBody", CS_ENTER,
		(Bullet*)pBullet, &Bullet::Hit);

	if (m_iDir == -1)
	{
		((MoveObject*)pBullet)->SetAngle(PI);

		float	x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
		float	y = GetCenter().y;

		pBullet->SetPos(x, y);
	}
	else
	{
		POSITION tPos;
		tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
		tPos.y = GetCenter().y;


		pBullet->SetPos(tPos);
	}


	pBullet->Release();
	pBullet = nullptr;
}*/
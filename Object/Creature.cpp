#include "Creature.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderReact.h"
#include "../Sound/SoundManager.h"
#include "CreatureSkill.h"
#include "../Scene/Scene.h"


Creature::Creature()
{
	m_fAtackTime = 0.f;
	m_fSkillTime = 0.f;
	m_bSkill = false;
}

Creature::Creature(const Creature & Creature) :MoveObject(Creature)
{
	m_fAtackTime = 0.f;
	m_fSkillTime = 0.f;
	m_bSkill = false;
}

Creature::~Creature()
{
	if (m_WeaponBody)
	{
		m_WeaponBody->Release();
		m_WeaponBody = nullptr;
	}
}

bool Creature::Init()
{
	SetPos(1700.f, 590.f);
	SetSize(200, 200.0f);
	SetSpeed(100.f);
	SetPivot(0.5f, 0.5f);
	//SetImageOffset(8.f, 8.f);





	ColliderReact* pReact = AddCollider<ColliderReact>("CreatureBody");


	pReact->SetRect(-34, -92, 34, 92);
	pReact->SetCollierOffset(20.f, 0.f);
	pReact->AddCollisionFunction(CS_ENTER, this, &Creature::Hit);


	pReact->Release();
	pReact = nullptr;


	Animation* pAnmation = CreateAnimation("CreatureAnimation");


	AddAnimationClip("CreatureNone", AT_ATLAS, AO_LOPE, 1.f, 3, 1, 0, 0, 3, 1,
		0.f, "CreatureNone", L"Enemy/Creature/Creature.bmp");
	SetAnimationClipColorKey("CreatureNone", 0, 255, 0);



	AddAnimationClip("CreatureAttack", AT_ATLAS, AO_LOPE, 3.f, 8, 1, 0, 0, 8, 1,
		0.f, "CreatureAttack", L"Enemy/Creature/CreatureAttack.bmp");
	SetAnimationClipColorKey("CreatureAttack", 0, 255, 0);


	AddAnimationClip("CreatureDie", AT_ATLAS, AO_LOPE, 0.5f, 5, 1, 0, 0, 5, 1,
		0.f, "CreatureDie", L"Enemy/Creature/CreatureDie.bmp");
	SetAnimationClipColorKey("CreatureDie", 0, 255, 0);

	m_pAnimation->SetCDefaultClip("CreatureNone");

	pAnmation->Release();
	pAnmation = nullptr;

	return true;
}

void Creature::Input(float fDeltaTime)
{
	MoveObject::Input(fDeltaTime);

}

int Creature::Update(float fDeltaTime)
{
	MoveObject::Update(fDeltaTime);



	MoveXFromSpeed(fDeltaTime, MD_BACK);



	if (m_pAnimation->GetCurrentStrClip() == "CreatureAttack")
	{
		if (m_pAnimation->GetMotionEnd())
		{
			Attack();
		}
	}

	


	if (!m_bSkill)
	{
		m_fAtackTime += fDeltaTime;
	}

	if (m_fAtackTime >= 5.f)
	{
		m_fAtackTime = 0.f;
		m_pAnimation->ChangeClip("CreatureAttack");
		SetSpeed(0.f);
	}



	if (m_bSkill)
	{
		m_fSkillTime += fDeltaTime;

		if (m_fSkillTime > 0.5f)
		{
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
			m_bSkill = false;
			SetSpeed(100.f);
			m_pAnimation->ReturenClip();
		}
	}


	return 0;
}

int Creature::LateUpdate(float fDeltaTime)
{
	MoveObject::LateUpdate(fDeltaTime);


	if (m_pAnimation->GetCurrentStrClip() == "CreatureDie")
	{
		if (m_pAnimation->GetMotionEnd())
		{
			Die();
			m_pScene->GoldUp(100);

		}
	}

	if (m_tPos.x <= 45.f)
	{
		m_pScene->GameOver(fDeltaTime);
	}

	return 0;
}

void Creature::Collision(float fDeltaTime)
{
	MoveObject::Collision(fDeltaTime);

}

void Creature::Render(HDC hDC, float fDeltaTime)
{
	MoveObject::Render(hDC, fDeltaTime);

}

Creature * Creature::Clone()
{
	return new Creature(*this);
}

void Creature::Hit(Collider * pSrc, Collider * pDest, float fDeltaTime)
{
	if (pSrc->GetTag() == "CreatureBody" && (pDest->GetTag() == "WeaponBody" ||
		pDest->GetTag() == "Skill1Range" || pDest->GetTag() == "SkillRange" ||
		pDest->GetTag() == "DraculaSkillBody" || pDest->GetTag() == "HorseBody")
		)
	{
		Creature* pCreature = (Creature*)pSrc->GetObject_();

		
		SetSpeed(0.f);
		pCreature->m_pAnimation->ChangeClip("CreatureDie");
		SoundManager::GetInst()->LoadSound("Enemy hit", false, "Enemy hit.wav");
		SoundManager::GetInst()->Play("Enemy hit");
	}
}

void Creature::Attack()
{
	for (int i = 0; i < 10; i++)
	{
		Object* pSkill = Object::CreateCloneObject("CreatureSkill", "CreatureSkill", SC_CURRENT, m_pLayer);

		pSkill->SetPos(m_tPos.x - 100 - i * 20, m_tPos.y - 350);


		pSkill->Release();
		pSkill = nullptr;
	}

	m_WeaponBody = AddCollider<ColliderReact>("CreatureSkill");
	m_WeaponBody->SetRect(-80.f, -330.f, 80.f, 330.f);
	m_WeaponBody->SetCollierOffset(-200.f, -150.f);
	m_WeaponBody->Release();

	m_fSkillTime = 0.f;
	m_bSkill = true;

}



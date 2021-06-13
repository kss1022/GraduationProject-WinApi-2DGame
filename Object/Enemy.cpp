#include "Enemy.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"
#include "../Object/Death.h"
#include "../Object/Skeleton.h"
#include "../Object/Creature.h"

#include "../Core/Input.h"
Enemy::Enemy()
{
}

Enemy::Enemy(const Enemy & Enemy) :StaticObject(Enemy)
{
}

Enemy::~Enemy()
{
}

bool Enemy::Init()
{
	m_pObject = nullptr;

	m_fMummyTime = 0.f;
	m_fSkeletonTime = 0.f;
	
	m_fDeathTime = 0.f;
	m_fCreatureTime = 0.f;
	return true;
}

void Enemy::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);	
}

int Enemy::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);

	m_fMummyTime += fDeltaTime;
	m_fSkeletonTime += fDeltaTime;
	m_fCreatureTime += fDeltaTime;

	if (m_fMummyTime >= 2.f)
	{
		SummonMummy();
		m_fMummyTime = 0.f;
	}


	if (m_fSkeletonTime >= 3.5f)
	{
		SummonSkeleton();
		m_fSkeletonTime = 0.f;
	}


	if (m_fCreatureTime >= 5.4f)
	{
		SummonCreature();
		m_fCreatureTime = 0.f;
	}


	if(m_fDeathTime >= 0.f)
	{
		m_fDeathTime += fDeltaTime;

		if (m_fDeathTime >= 20.f)
		{
			SummonDeath();
			m_fDeathTime = -1.f;
		}
	}



	return 0;
}

int Enemy::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);

	return 0;
}

void Enemy::Collision(float fDeltaTime)
{
	StaticObject::Collision(fDeltaTime);

}

void Enemy::Render(HDC hDC, float fDeltaTime)
{
	StaticObject::Render(hDC, fDeltaTime);
}

Enemy * Enemy::Clone()
{
	return new Enemy(*this);
}

Object * Enemy::GetObject_() const
{
	return m_pObject;
}

void Enemy::SetObject(Object * obj)
{
	m_pObject = obj;
}



void Enemy::SummonSkeleton()
{
	
	Object* pSkeleton = Object::CreateCloneObject("Skeleton", "SkeletonProtocal", m_pScene->GetSceneType(), m_pLayer);
	
	pSkeleton->m_pAnimation->SetObject(pSkeleton);


	pSkeleton->m_pAnimation->ChangeClip("SkeletonMove");


	pSkeleton->Release();
	pSkeleton = nullptr;
}

void Enemy::SummonDeath()
{
	Object* pDeath = Object::CreateCloneObject("Death", "DeathProtoType", m_pScene->GetSceneType(), m_pLayer);

	pDeath->m_pAnimation->SetObject(pDeath);
	((Death*)pDeath)->SetObject(m_pObject);

	pDeath->Release();
	pDeath = nullptr;
}

void Enemy::SummonCreature()
{
	Object* pCreature = Object::CreateCloneObject("Creature", "CreatureProtoType", m_pScene->GetSceneType(), m_pLayer);

	pCreature->m_pAnimation->SetObject(pCreature);

	pCreature->Release();
	pCreature = nullptr;
}


void Enemy::SummonMummy()
{
	Object* pCreature = Object::CreateCloneObject("Mummy", "MummyProtoType", m_pScene->GetSceneType(), m_pLayer);

	pCreature->m_pAnimation->SetObject(pCreature);

	pCreature->Release();
	pCreature = nullptr;
}



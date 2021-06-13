#include "CollisionManager.h"
#include "../Object/Object.h"
#include "../Collider/Collider.h"

CollisionManager* CollisionManager::m_pInst = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager * CollisionManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new CollisionManager;
	}
	return m_pInst;
}

void CollisionManager::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

void CollisionManager::AddObject(Object * pObj)
{
	if (pObj->CheckCollider())
	{
		m_CollisionList.push_back(pObj);
	}
}

void CollisionManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}

	//������Ʈ �浹ó��

	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd= m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; iter++)
	{
		list<Object*>::iterator iter1 = iter;
		list<Object*>::iterator iter1End = m_CollisionList.end();

		iter1++;

		for (iter1; iter1 != iter1End; iter1++)
		{
			Collision(*iter, *iter1, fDeltaTime);
		}

	}

	m_CollisionList.clear();
}

bool CollisionManager::Collision(Object* pSrc, Object* pDest, float fDeltaTime)
{
	const list<Collider*>* pSrcList = pSrc->GetColliderList();
	const list<Collider*>* pDestList = pDest->GetColliderList();



	list<Collider*>::const_iterator iterSrc;
	list<Collider*>::const_iterator iterSrcEnd = pSrcList->end();


	list<Collider*>::const_iterator iterDest;
	list<Collider*>::const_iterator iterDestEnd = pDestList->end();


	bool bCollision = false;

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; iterSrc++)
	{
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; iterDest++)
		{
			if ( (*iterSrc)->Collision(*iterDest) )
			{
				bCollision = true;

				(*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

				//�浹��Ͽ� ���� ->  ó�� �浹��
				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);


					(*iterSrc)->Callfunction(CS_ENTER, *iterDest, fDeltaTime);
					(*iterDest)->Callfunction(CS_ENTER, *iterSrc, fDeltaTime);
				}
				//��� �浹������
				else
				{
					(*iterSrc)->Callfunction(CS_STAY, *iterDest, fDeltaTime);
					(*iterDest)->Callfunction(CS_STAY, *iterSrc, fDeltaTime);
				}

			}
			//�浹��Ͽ� ������  �浹���� �ʰ� �ִ°��
			else if((*iterSrc)->CheckCollisionList(*iterDest))
			{
				(*iterSrc)->Callfunction(CS_LEAVE, *iterDest, fDeltaTime);
				(*iterDest)->Callfunction(CS_LEAVE, *iterSrc, fDeltaTime);

				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc);
			}
		}

	}
	return bCollision;
}

void CollisionManager::Clear()
{
	m_CollisionList.clear();
}

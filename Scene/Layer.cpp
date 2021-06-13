#include "Layer.h"
#include "../Object/Object.h"
#include "../Collider/CollisionManager.h"
Layer* Layer::m_pInst = nullptr;

Layer::Layer() :m_iZOrder(0), m_strTag(""), m_pScene(nullptr), m_bEnable(true), m_bLife(true)
{
}

Layer::~Layer()
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; iter++)
	{
		Object::EraseObject(*iter);
		(*iter)->Release();
		*iter = nullptr;
	}

	m_ObjectList.clear();
}

Layer * Layer::GetInst()
{
	if (m_pInst)
	{
		m_pInst = new Layer;
	}
	return m_pInst;
}

void Layer::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

bool Layer::Init()
{
	return true;
}

void Layer::Input(float fDeltaTime)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Input(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			Object::EraseObject(*iter);
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else iter++;
	}
}

int Layer::Update(float fDeltaTime)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Update(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			Object::EraseObject(*iter);
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else iter++;
	}
	return 0;
}

int Layer::LateUpdate(float fDeltaTime)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			Object::EraseObject(*iter);
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else iter++;
	}
	return 0;
}

void Layer::Collision(float fDeltaTime)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Collision(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			Object::EraseObject(*iter);
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else
		{
			CollisionManager::GetInst()->AddObject(*iter);
			iter++;
		}
	}
}

void Layer::Render(HDC hDC, float fDeltaTime)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}
		
		(*iter)->Render(hDC,fDeltaTime);


		if (!(*iter)->GetLife())
		{
			Object::EraseObject(*iter);
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else iter++;
	}
}

void Layer::AddObject(Object * pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);

	pObj->AddRef();
	m_ObjectList.push_back(pObj);
}
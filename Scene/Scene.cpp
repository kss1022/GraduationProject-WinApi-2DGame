#include "Scene.h"
#include "Layer.h"
#include "../Object/Object.h"


unordered_map<string, Object*> Scene::m_PrototypeMap[SC_END] = {};

Scene::Scene()
{
	Layer* pLayer = CreateLayer("UI", INT_MAX);
	pLayer = CreateLayer("HUD", INT_MAX-1);
	pLayer = CreateLayer("Default", 1);
	pLayer = CreateLayer("STAGE", 0);
	m_eSceneType = SC_CURRENT;

	m_fPlayTime = 0.f;
}

Scene::~Scene()
{

	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; iter++)
	{
		delete *iter;
		*iter = nullptr;
	}

	m_LayerList.clear();


	ErasePrototype(m_eSceneType);
}


void Scene::ErasePrototype(const string & strTag,SCENE_CREATE sc)
{
	unordered_map<string, Object*>::iterator iter = m_PrototypeMap[sc].find(strTag);

	if (!iter->second)
	{
		return;
	}

	iter->second->Release();
	iter->second = nullptr;

	m_PrototypeMap[sc].erase(iter);
}

void Scene::ErasePrototype(SCENE_CREATE sc)
{
	unordered_map<string, Object*>::iterator iter;
	unordered_map<string, Object*>::iterator iterEnd = m_PrototypeMap[sc].end();

	for (iter = m_PrototypeMap[sc].begin(); iter != iterEnd; iter++)
	{
		iter->second->Release();
		iter->second = nullptr;
	}

	m_PrototypeMap[sc].clear();
}


Object * Scene::FindPrototype(const string & strKey, SCENE_CREATE sc)
{
	unordered_map<string, Object*>::iterator iter = m_PrototypeMap[sc].find(strKey);

	if (iter == m_PrototypeMap[sc].end())
	{
		return nullptr;
	}


	return iter->second;
}

void Scene::ChangeProtoType()
{
	ErasePrototype(SC_CURRENT);
	m_PrototypeMap[SC_CURRENT] = m_PrototypeMap[SC_NEXT];

	m_PrototypeMap[SC_NEXT].clear();
}






Layer * Scene::CreateLayer(const string & strTag, int iZOrder)
{
	Layer* pLayer = new Layer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	//Layer Á¤·Ä
	if (m_LayerList.size() >= 2)
	{
		m_LayerList.sort(Scene::LayerSort);
	}

	return pLayer;
}

bool Scene::LayerSort(Layer * pLayer1, Layer * pLayer2)
{
	return pLayer1->GetZOrder() < pLayer2->GetZOrder();
}

Layer * Scene::FindLayer(const string & str)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; iter++)
	{
		if ((*iter)->GetTag() == str)
		{
			return *iter;
		}
	}


	return nullptr;
}






bool Scene::Init()
{
	m_iGold = 500;
	return true;
}

void Scene::Input(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Input(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			delete *iter;
			*iter = nullptr;
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else iter++;
	}
}

int Scene::Update(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Update(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			delete *iter;
			*iter = nullptr;
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else iter++;
	}
	return 0;
}

int Scene::LateUpdate(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			delete *iter;
			*iter = nullptr;
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else iter++;
	}
	return 0;
}

void Scene::Collision(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Collision(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			delete *iter;
			*iter = nullptr;
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else iter++;
	}
}

void Scene::Render(HDC hDC, float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);


		if (!(*iter)->GetLife())
		{
			delete *iter;
			*iter = nullptr;
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else iter++;
	}
}
void Scene::GoldUp(int iMoney)
{
	m_iGold += iMoney;
}

int Scene::GetGold() const
{
	return m_iGold;
}

float Scene::GetPlayTime() const
{
	return m_fPlayTime;
}

void Scene::ChangeScene(float fTime)
{
}

void Scene::GameOver(float fTime)
{
}


SCENE_CREATE Scene::GetSceneType() const
{
	return m_eSceneType;
}

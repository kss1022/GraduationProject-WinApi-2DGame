#pragma once

#include "../Game.h"

class Scene
{
private:
	friend class SceneManager;

protected:
	Scene();
	virtual ~Scene() = 0;


private:
	static unordered_map<string, class Object*>	m_PrototypeMap[SC_END];

public:
	static void		ErasePrototype(const string& strTag , SCENE_CREATE sc);
	static void		ErasePrototype(SCENE_CREATE sc);

	static Object* FindPrototype(const string& strKey, SCENE_CREATE sc);

	template<typename T>
	static T* CreatePrototype(const string& strTag, SCENE_CREATE sc);

	static void ChangeProtoType();


protected:
	list<class Layer*> m_LayerList;
	SCENE_CREATE	m_eSceneType;
	class Layer* CreateLayer(const string& strTag, int iZOrder = 0);


public:
	static bool LayerSort(class Layer* pLayer1, class Layer* pLayer2);

	class Layer* FindLayer(const string& str);

	inline void SetSceneType( SCENE_CREATE sc);
	SCENE_CREATE GetSceneType() const;

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);


protected:
	int m_iGold;
	float m_fPlayTime;

public:
	void GoldUp(int iMoney);
	int	GetGold() const;
	

	float GetPlayTime() const;





public:
	virtual void ChangeScene(float fTime) ;
	virtual void GameOver(float fTime) ;
};

template<typename T>
T * Scene::CreatePrototype(const string & strTag, SCENE_CREATE sc)
{
	T* pObj = new T;

	pObj->SetTag(strTag);


	if (!pObj->Init())
	{
		pObj->Release();
		pObj = nullptr;

		return nullptr;
	}

	pObj->AddRef();
	m_PrototypeMap[sc].insert(make_pair(strTag, pObj));

	return pObj;
}


 void Scene::SetSceneType( SCENE_CREATE sc)
{
	m_eSceneType = sc;
}

 
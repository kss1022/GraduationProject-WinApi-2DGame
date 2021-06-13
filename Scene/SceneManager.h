#pragma once

#include"../Game.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

	static SceneManager* m_pInst;
	

public:
	static SceneManager* GetInst();
	static void DestroyInst();

	bool Init();

private:
	class Scene* m_pScene;
	class Scene* m_pNextScene;

public:
	template<typename T>
	T* CreateScene(SCENE_CREATE sc = SC_CURRENT);


public:
	void Input(float fDeltaTime);
	SCENE_CHANGE Update(float fDeltaTime);
	SCENE_CHANGE LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC,float fDeltaTime);

private:
	SCENE_CHANGE ChangeScene();
};


template<typename T>
inline T* SceneManager::CreateScene(SCENE_CREATE sc)
{
	T* pScene = new T;

	pScene->SetSceneType(sc);

	if (!pScene->Init())
	{
		delete pScene;
		pScene = nullptr;
	}

	switch (sc)
	{
	case SC_CURRENT:
		delete m_pScene;
		m_pScene = pScene;
		break;

	case SC_NEXT:
		delete m_pNextScene;
		m_pNextScene = pScene;
		break;
	default:
		break;
	}


	return pScene;
}


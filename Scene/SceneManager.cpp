#include "SceneManager.h"
#include "InGameScene.h"
#include "StartScene.h"
#include "../Collider/CollisionManager.h"
#include "../Core/Camera.h"
SceneManager* SceneManager::m_pInst = nullptr;

SceneManager::SceneManager() :m_pScene(nullptr), m_pNextScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	m_pScene = nullptr;
}


SceneManager * SceneManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new SceneManager;
	}

	return m_pInst;
}

void SceneManager::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

bool SceneManager::Init()
{
	CreateScene<StartScene>(SC_CURRENT);

	return true;
}



void SceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

SCENE_CHANGE SceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	return ChangeScene();

}

SCENE_CHANGE SceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
	return ChangeScene();
}

void SceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void SceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}

SCENE_CHANGE SceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
		m_pScene = m_pNextScene;
		m_pNextScene = nullptr;

		CollisionManager::GetInst()->Clear();

		m_pScene->SetSceneType(SC_CURRENT);
		Scene::ChangeProtoType();

		//Camera::GetInst()->DestroyInst();
		//Camera::GetInst()->Init(POSITION(0.f, 0.f), RESOLUTION(1280,720), RESOLUTION(1500, 1200));

		return SC_CHANGE;
	}
	return SC_NONE;
}


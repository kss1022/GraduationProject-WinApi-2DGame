#include "GameOverScene.h"
#include "../Core.h"
#include "../Scene/Layer.h"
#include "../Object/UIPanel.h"

#include "../Sound/SoundManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/StartScene.h"


GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
	SoundManager::GetInst()->Stop(ST_BGM);
}

bool GameOverScene::Init()
{
	SoundManager::GetInst()->Stop(ST_BGM);

	SoundManager::GetInst()->LoadSound("GameOver", true, "GameOver.mp3");
	SoundManager::GetInst()->Play("GameOver");
	

	if (!Scene::Init())
	{
		return false;
	}


	Layer* pLayer = FindLayer("UI");

	UIPanel* pBackPanel = Object::CreateObj<UIPanel>("BackPanel", pLayer);


	pBackPanel->SetSize(Core::GetInst()->GetResoulution().iW, Core::GetInst()->GetResoulution().iH);

	pBackPanel->SetTexture("GameOver", L"Stage/GameOver.bmp");


	pBackPanel->Release();
	pBackPanel = nullptr;




	return true;
}

void GameOverScene::Input(float fDeltaTime)
{
	Scene::Input(fDeltaTime);

	for (int i = 8; i < 255; i++)
	{
		if (GetAsyncKeyState(i) && m_fPlayTime >= 5.f)
		{
			SceneManager::GetInst()->CreateScene<StartScene>(SC_NEXT);
		}
	}
}

int GameOverScene::Update(float fDeltaTime)
{
	Scene::Update(fDeltaTime);

	m_fPlayTime += fDeltaTime;

	return 0;
}


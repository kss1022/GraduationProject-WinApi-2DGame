#include "GameWinScene.h"
#include "../Core.h"
#include "../Scene/Layer.h"
#include "../Object/UIPanel.h"
#include "../Sound/SoundManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/StartScene.h"
#include "../Scene/EndingScene.h"

#include "../Object/Castle.h"

GameWinScene::GameWinScene()
{
}

GameWinScene::~GameWinScene()
{
}

bool GameWinScene::Init()
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

	pBackPanel->SetTexture("GameWin", L"Stage/GameWin.bmp");


	pBackPanel->Release();
	pBackPanel = nullptr;




	Castle* pCastle = Object::CreateObj<Castle>("Castle", pLayer);
	pCastle->Release();
	pCastle = nullptr;



	return true;
}

void GameWinScene::Input(float fDeltaTime)
{
	Scene::Input(fDeltaTime);

	for (int i = 8; i < 255; i++)
	{
		if (GetAsyncKeyState(i) && m_fPlayTime >= 5.f)
		{
			//Core::GetInst()->DestroyGame();
			SceneManager::GetInst()->CreateScene<EndingScene>(SC_NEXT);
		}
	}
}

int GameWinScene::Update(float fDeltaTime)
{
	Scene::Update(fDeltaTime);
	m_fPlayTime += fDeltaTime;

	return 0;
}


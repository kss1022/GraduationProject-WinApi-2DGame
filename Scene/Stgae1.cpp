#include "InGameScene.h"

#include "Stgae1.h"
#include "../Core/Input.h"
#include "../Core/Camera.h"
#include "../Sound/SoundManager.h"
#include "../Scene/Layer.h"
#include "../Collider/ColliderPixel.h"
#include "../Object/StageMap1.h"
#include "../Object/Stage.h"




#include "../Object/Enemy.h"	
#include "../Object/Skeleton.h"
#include "../Object/SkeletonBullet.h"
#include "../Object/Death.h"
#include "../Object/DeathWeapon.h"
#include "../Object/Creature.h"
#include "../Object/CreatureSkill.h"
#include "../Object/Mummy.h"

#include "../Object/Player.h"
#include "../Object/HPBar.h"
#include "../Object/MPBar.h"
#include "../Object/Skill1.h"
#include "../Object/Skill2.h"

#include "../Object/Friendly.h"
#include "../Object/Horse.h"
#include "../Object/HorseUI.h"
#include "../Object/Dracula.h"
#include "../Object/DraculaSkill.h"
#include "../Object/DraculaUI.h"

#include "../Object/StatusUI.h"
#include "../Object/Number.h"


#include "../Scene/GameOverScene.h"
#include "../Scene/GameWinScene.h"
#include "../Scene/SceneManager.h"

#include "../Object/Castle.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	if (m_pTimeNumber100)
	{
		m_pTimeNumber100->Release();
		m_pTimeNumber100 = nullptr;
	}

	if (m_pTimeNumber10)
	{
		m_pTimeNumber10->Release();
		m_pTimeNumber10 = nullptr;
	}


	if (m_pTimeNumber1)
	{
		m_pTimeNumber1->Release();
		m_pTimeNumber1 = nullptr;
	}


	if (m_pGoldNumber100)
	{
		m_pGoldNumber100->Release();
		m_pGoldNumber100 = nullptr;
	}
	if (m_pGoldNumber1000)
	{
		m_pGoldNumber1000->Release();
		m_pGoldNumber1000 = nullptr;
	}

}


bool Stage1::Init()
{

	SoundManager::GetInst()->Stop(ST_BGM);

	SoundManager::GetInst()->LoadSound("Stage1", true, "Level1.wav");
	SoundManager::GetInst()->Play("Stage1");
	SoundManager::GetInst()->Volume(ST_BGM, 0.3f);




	if (!Scene::Init())
	{
		return false;
	}

	Layer* pStageLayer = FindLayer("STAGE");
	StageMap1* pStage = Object::CreateObj<StageMap1>("STAGE", pStageLayer);

	ColliderPixel * pPixel = pStage->AddCollider<ColliderPixel>("StageColl");
	pPixel->SetPixelInfo("Stage/StagePixel.bmp");
	pPixel->Release();
	pPixel = nullptr;


	pStage->Release();
	pStage = nullptr;



	Layer* pDefaultLayer = FindLayer("Default");
	Player* pPlayer = Object::CreateObj<Player>("Player", pDefaultLayer);


	Camera::GetInst()->SetTarget(pPlayer);
	Camera::GetInst()->SetPivot(0.8f, 0.3f);


	HPBar* pPlayerHP = Object::CreateObj<HPBar>("PlayerHPBar", pDefaultLayer);
	pPlayerHP->SetObject(pPlayer);
	pPlayerHP->Release();
	pPlayerHP = nullptr;


	MPBar* pPlayerMP = Object::CreateObj<MPBar>("PlayerMP", pDefaultLayer);
	pPlayerMP->SetObject(pPlayer);
	pPlayerMP->Release();
	pPlayerMP = nullptr;

	Enemy* pEnemy = Object::CreateObj<Enemy>("Enemy", pDefaultLayer);
	pEnemy->SetObject(pPlayer);
	pEnemy->Release();
	pEnemy = nullptr;



	pPlayer->Release();
	pPlayer = nullptr;




	Friendly* pFriendly = Object::CreateObj<Friendly>("Friendly", pDefaultLayer);
	pFriendly->Release();
	pFriendly = nullptr;



	//플레이어 상태UI
//	PlayerStatus* pPlayerStatus = Object::CreateObj<PlayerStatus>("PlayerStatus", pDefaultLayer);
//	pPlayerStatus->SetSize(1280.f, 147.f);
//	pPlayerStatus->SetPos(0, 573);
//	pPlayerStatus->SetTexture("BottomUI", L"BottomUI2.bmp");
//	pPlayerStatus->SetColorKey(255, 255, 255);
//	pPlayerStatus->Release();
//	pPlayerStatus = nullptr;


	m_pTimeNumber1 = Object::CreateObj<Number>("Number", pDefaultLayer);
	m_pTimeNumber1->SetPos(800.f, 0.f);
	m_pTimeNumber10 = Object::CreateObj<Number>("Number", pDefaultLayer);
	m_pTimeNumber10->SetPos(740.f, 0.f);
	m_pTimeNumber100 = Object::CreateObj<Number>("Number", pDefaultLayer);
	m_pTimeNumber100->SetPos(680.f, 0.f);
	
	StatusUI*  TimeUI = Object::CreateObj<StatusUI>("Time", pDefaultLayer);
	TimeUI->SetTexture("Time", L"Number/Time.bmp");
	TimeUI->SetPos(620.f, 0.f);
	TimeUI->SetColorKey(255, 255, 255);
	TimeUI->Release();
	TimeUI = nullptr;


	
	Number* pGoldNumber1 = Object::CreateObj<Number>("Number", pDefaultLayer);
	pGoldNumber1->SetPos(450.f, 0.f);
	pGoldNumber1->Release();
	pGoldNumber1 = nullptr;

	Number* m_pGoldNumber10 = Object::CreateObj<Number>("Number", pDefaultLayer);
	m_pGoldNumber10->SetPos(390.f, 0.f);
	m_pGoldNumber10->Release();
	m_pGoldNumber10 = nullptr;

	m_pGoldNumber100 = Object::CreateObj<Number>("Number", pDefaultLayer);
	m_pGoldNumber100->SetPos(330.f, 0.f);	
	m_pGoldNumber1000 = Object::CreateObj<Number>("Number", pDefaultLayer);
	m_pGoldNumber1000->SetPos(270.f, 0.f);


	StatusUI* MoneyUI = Object::CreateObj<StatusUI>("$", pDefaultLayer);
	MoneyUI->SetPos(210.f, 0.f);
	MoneyUI->SetTexture("$", L"Number/Money.bmp");
	MoneyUI->SetColorKey(255, 255, 255);
	MoneyUI->Release();
	MoneyUI = nullptr;

	HorseUI *m_pHorseUI = Object::CreateObj<HorseUI>("HorseUI", pDefaultLayer);
	m_pHorseUI->SetPos(0.f, 0.f);
	m_pHorseUI->Release();
	m_pHorseUI = nullptr;
	
	DraculaUI *m_pDraculaUI = Object::CreateObj<DraculaUI>("DraculaUI", pDefaultLayer);
	m_pDraculaUI->SetPos(100.f, 0.f);
	m_pDraculaUI->Release();
	m_pDraculaUI = nullptr;





	Skeleton* pSkeletonPrototype = Scene::CreatePrototype<Skeleton>("Skeleton", m_eSceneType);
	pSkeletonPrototype->Release();
	pSkeletonPrototype = nullptr;

	SkeletonBullet* pSkeletonBulletPrototype = Scene::CreatePrototype<SkeletonBullet>("SkeletonBullet", m_eSceneType);
	pSkeletonBulletPrototype->Release();
	pSkeletonBulletPrototype = nullptr;

	Death* pDeathnPrototype = Scene::CreatePrototype<Death>("Death", m_eSceneType);
	pDeathnPrototype->Release();
	pDeathnPrototype = nullptr;

	DeathWeapon* pDeathWeaponPrototype = Scene::CreatePrototype<DeathWeapon>("DeathWeapon", m_eSceneType);
	pDeathWeaponPrototype->Release();
	pDeathWeaponPrototype = nullptr;


	Creature* pCreaturePrototype = Scene::CreatePrototype<Creature>("Creature", m_eSceneType);
	pCreaturePrototype->Release();
	pCreaturePrototype = nullptr;

	CreatureSkill* pCreatureSkillPrototype = Scene::CreatePrototype<CreatureSkill>("CreatureSkill", m_eSceneType);
	pCreatureSkillPrototype->Release();
	pCreatureSkillPrototype = nullptr;

	Mummy* pMummy = Scene::CreatePrototype<Mummy>("Mummy", m_eSceneType);
	pMummy->Release();
	pMummy = nullptr;



	Horse* pHorsePrototype = Scene::CreatePrototype<Horse>("Horse", m_eSceneType);

	pHorsePrototype->Release();
	pHorsePrototype = nullptr;

	Dracula* pDraculaPrototype = Scene::CreatePrototype<Dracula>("Dracula", m_eSceneType);
	pDraculaPrototype->Release();
	pDraculaPrototype = nullptr;

	DraculaSkill* pDraculaSkillPrototype = Scene::CreatePrototype<DraculaSkill>("DraculaSkill", m_eSceneType);
	pDraculaSkillPrototype->Release();
	pDraculaSkillPrototype = nullptr;


	Skill1* pSkill1 = Scene::CreatePrototype<Skill1>("Skill1Protocal", m_eSceneType);
	pSkill1->Release();
	pSkill1 = nullptr;

	Skill2* pSkill2 = Scene::CreatePrototype<Skill2>("Skill2Protocal", m_eSceneType);
	pSkill2->Release();
	pSkill2 = nullptr;
	return true;
}

int Stage1::Update(float fDeltaTime)
{
	Scene::Update(fDeltaTime);

	m_fPlayTime += fDeltaTime;

	int time = static_cast<int>(m_fPlayTime);
	m_pTimeNumber1->SetNumber(time % 10);
	
	time /= 10;
	m_pTimeNumber10->SetNumber(time %10);

	
	time /= 10;
	m_pTimeNumber100->SetNumber(time % 10);


	int iGold = m_iGold / 100;
	m_pGoldNumber100->SetNumber(iGold % 10);

	iGold /= 10;
	m_pGoldNumber1000->SetNumber(iGold % 10);
	

	return 0;
}

void Stage1::Render(HDC hDC, float fDeltaTime)
{
	Scene::Render(hDC, fDeltaTime);



	/*
	wchar_t strPlayTime[32] = {};

	wsprintf(strPlayTime, L"Time  : %d", static_cast<int>(m_fPlayTime));

	TextOut(hDC, 600, 0, strPlayTime, lstrlen(strPlayTime));
	*/


	/*
	wchar_t strGold[32] = {};

	wsprintf(strGold, L"Gold  : %d", static_cast<int>(m_iGold));

	TextOut(hDC, 300, 0, strGold, lstrlen(strGold));
	*/
}

void Stage1::ChangeScene(float fTime)
{
	Scene::ChangeScene(fTime);
	SceneManager::GetInst()->CreateScene<GameWinScene>(SC_NEXT);
}

void Stage1::GameOver(float fTime)
{
	Scene::GameOver(fTime);
	SceneManager::GetInst()->CreateScene<GameOverScene>(SC_NEXT);
}




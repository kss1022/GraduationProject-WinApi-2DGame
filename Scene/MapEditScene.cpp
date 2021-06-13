#include "MapEditScene.h"

#include "../Core.h"
#include "../Core/Camera.h"
#include "SceneManager.h"
#include "InGameScene.h"
#include "StartScene.h"
#include "../Scene/Layer.h"

#include "../Collider/ColliderReact.h"

#include "../Object/Object.h"
#include "../Object/UIButton.h"
#include "../Object/UIPanel.h"
#include "../Object/Stage.h"
#include "../Core/Input.h"

#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../resource.h"
#include "../Core/PathManager.h"
#include "../Core.h"


#include "../Object/StageMap1.h"
wchar_t	MapEditScene::m_strText[MAX_PATH] = {};


MapEditScene::MapEditScene() : m_eTEM(TEM_TEXTURE)
{
}

MapEditScene::~MapEditScene()
{

	vector<Texture*>::iterator iter;
	vector<Texture*>::iterator iterEnd = m_vecTexture.end();

	for (iter = m_vecTexture.begin(); iter != iterEnd; iter++)
	{
		(*iter)->Release();
		*iter = nullptr;
	}

	m_vecTexture.clear();

	m_pStage->Release();
	m_pStage = nullptr;

}


bool MapEditScene::Init()
{
	if (!Scene::Init())
	{
		return false;
	}

	Camera::GetInst()->SetWolrdRS(1500, 1200);

	Texture* pNoneTexture = ResourceManager::GetInst()->LoadTexture(
		"TileNone", L"Tile/OptionNone.bmp");
	pNoneTexture->SetColorKey(255, 0, 255);
	pNoneTexture->Release();
	pNoneTexture = nullptr;


	Texture* pNoMoveTexture = ResourceManager::GetInst()->LoadTexture(
		"TileNoMove", L"Tile/OptionNoMove.bmp");
	pNoMoveTexture->SetColorKey(255, 0, 255);
	pNoMoveTexture->Release();
	pNoMoveTexture = nullptr;



	Layer* pLayer = FindLayer("STAGE");

	m_pStage = Object::CreateObj<Stage>("STAGE", pLayer);

	m_pStage->CreateTile(30, 24, 50, 50, "BaseTile", L"Tile/BaseTile.bmp");

	m_vecTexture.reserve(5);


	Texture* m_pTexture = ResourceManager::GetInst()->LoadTexture(
		"BaseTile", L"Tile/BaseTile.bmp");
	m_vecTexture.push_back(m_pTexture);


	m_pTexture = ResourceManager::GetInst()->LoadTexture(
		"IceTile", L"Tile/IceTile.bmp");
	m_vecTexture.push_back(m_pTexture);


	m_pTexture = ResourceManager::GetInst()->LoadTexture(
		"FireTile", L"Tile/FireTile.bmp");
	m_vecTexture.push_back(m_pTexture);


	m_pTexture = ResourceManager::GetInst()->LoadTexture(
		"WaterTile", L"Tile/WaterTile.bmp");
	m_vecTexture.push_back(m_pTexture);

	m_iEditTileTex = 0;
	m_eEditOption = TO_NONE;

	Input::GetInst()->AddKey("Save", 'S', VK_CONTROL);
	Input::GetInst()->AddKey("Load", 'O', VK_CONTROL);

	


	return true;
}

void MapEditScene::Input(float fDeltaTime)
{
	Scene::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000)
	{
		Camera::GetInst()->Scroll(0.f, -300.f * fDeltaTime);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		Camera::GetInst()->Scroll(0.f, 300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		Camera::GetInst()->Scroll(-300.f * fDeltaTime, 0.f);
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		Camera::GetInst()->Scroll(300.f * fDeltaTime, 0.f);
	}


	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		m_eTEM = TEM_TEXTURE;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		m_eTEM = TEM_OPTION;
	}


	if (GetAsyncKeyState('1') & 0x8000)
	{
		switch (m_eTEM)
		{
		case TEM_TEXTURE:
			m_iEditTileTex = 0;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NONE;
			break;
		default:
			break;
		}
	}

	if (GetAsyncKeyState('2') & 0x8000)
	{
		switch (m_eTEM)
		{
		case TEM_TEXTURE:
			m_iEditTileTex = 1;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		default:
			break;
		}
	}

	if (GetAsyncKeyState('3') & 0x8000)
	{
		switch (m_eTEM)
		{
		case TEM_TEXTURE:
			m_iEditTileTex = 2;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		default:
			break;
		}
	}

	if (GetAsyncKeyState('4') & 0x8000)
	{
		switch (m_eTEM)
		{
		case TEM_TEXTURE:
			m_iEditTileTex = 3;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		default:
			break;
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		Core::GetInst()->DestroyGame();
	}


	if (KEYPRESS("MouseLButton"))
	{
		POSITION tMouseWorldPos = Input::GetInst()->GetMouseWorldPos();

		switch (m_eTEM)
		{
		case TEM_TEXTURE:
			m_pStage->ChangeTileTexture(tMouseWorldPos, m_vecTexture[m_iEditTileTex]);
			break;
		case TEM_OPTION:
			m_pStage->ChangeTileOption(tMouseWorldPos, m_eEditOption);
			break;
		default:
			break;
		}
	}



	if (KEYPRESS("Save"))
	{
		ShowCursor(TRUE);
		DialogBox(Core::GetInst()->GetWindowInsatnce(), MAKEINTRESOURCE(IDD_DIALOG1),
			Core::GetInst()->GetWindowHandle(), MapEditScene::DlgProc);
		ShowCursor(FALSE);


		//파일 명을 이용하여 저장한다.

		char strFileName[MAX_PATH] = {};
		 WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName, lstrlen(m_strText), 0, 0);

		 m_pStage->SaveFromPath(strFileName);
	}

	if (KEYPRESS("Load"))
	{
		ShowCursor(TRUE);
		DialogBox(Core::GetInst()->GetWindowInsatnce(), MAKEINTRESOURCE(IDD_DIALOG1),
			Core::GetInst()->GetWindowHandle(), MapEditScene::DlgProc);
		ShowCursor(FALSE);


		//파일 명을 이용하여 로드한다.

		char strFileName[MAX_PATH] = {};
		WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName, lstrlen(m_strText), 0, 0);

		if (!m_pStage)
		{
			Layer* pLayer = FindLayer("STAGE");

			m_pStage = Object::CreateObj<Stage>("STAGE", pLayer);
		}

		m_pStage->LoadFromPath(strFileName);
	}

}

INT_PTR MapEditScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			//Edit Box에서 문자열을 얻어온다
			memset(m_strText, 0, sizeof(wchar_t) * MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDIT1, m_strText, MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		default:
			break;
		}
		return FALSE;
	}
	return FALSE;
}


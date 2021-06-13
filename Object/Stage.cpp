#include "Stage.h"
#include "../Core.h"
#include "../Resource/Texture.h"
#include "../Core/Camera.h"
#include "../Object/Tile.h"
#include "../Scene/Layer.h"

#include "../Core/PathManager.h"
Stage::Stage()
{
}

Stage::Stage(const Stage & stage) : StaticObject(stage)
{
	ClearTile();

	for (size_t i = 0; i < stage.m_vecTile.size(); i++)
	{
		m_vecTile.push_back(stage.m_vecTile[i]->Clone());
	}
}

Stage::~Stage()
{
	ClearTile();
}

void Stage::CreateTile(int iNumX, int iNumY, int iSIzeX, int iSizeY,
	const string & strTag, const wchar_t * pFIleName, const string & strPathKey)
{
	ClearTile();

	m_iTileNumX = iNumX;
	m_iTileNumY = iNumY;
	m_iTileSizeX = iSIzeX;
	m_iTileSizeY = iSizeY;

	for (int i = 0; i < iNumY; i++)
	{
		for (int j = 0; j < iNumX; j++)
		{
			Tile* pTile = Object::CreateObj<Tile>("Tile");

			pTile->SetSize(iSIzeX, iSizeY);
			pTile->SetPos(j * iSIzeX, i * iSizeY);

			pTile->SetTexture(strTag, pFIleName, strPathKey);

			m_vecTile.push_back(pTile);
		}
	}
}

void Stage::ChangeTileTexture(const POSITION & tPos, Texture * pTexture)
{
	int iIndex = GetTileIndex(tPos);

	if (iIndex == -1) return;

	m_vecTile[iIndex]->SetTexture(pTexture);
}

void Stage::ChangeTileOption(const POSITION & tPos, TILE_OPTION eOption)
{
	int iIndex = GetTileIndex(tPos);

	if (iIndex == -1) return;

	m_vecTile[iIndex]->SetTileOption(eOption);
}

int Stage::GetTileIndex(const POSITION & tPos)
{
	return GetTileIndex(tPos.x,tPos.y);
}

int Stage::GetTileIndex(float x, float y)
{
	int iX = static_cast<int>(x) / m_iTileSizeX;
	int iY = static_cast<int>(y) / m_iTileSizeY;

	if (iX < 0 || iX >= m_iTileNumX)
	{
		return -1;
	}

	if (iY < 0 || iY >= m_iTileNumY)
	{
		return -1;
	}

	return iY * m_iTileNumX + iX;
}



bool Stage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1500.f, 1200.f);
	SetPivot(0.0f, 0.0f);

	SetTexture("Stage1", L"Stage1.bmp");
	return true;
}



void Stage::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);
}

int Stage::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);


	return 0;
}

int Stage::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);
	return 0;
}

void Stage::Collision(float fDeltaTime)
{
	StaticObject::Collision(fDeltaTime);
}

void Stage::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture)
	{
		POSITION	tPos = m_tPos - m_tSize * m_tPivot;

		POSITION	tCamPos = Camera::GetInst()->GetPos();


		BitBlt(hDC, tPos.x, tPos.y, Core::GetInst()->GetResoulution().iW, Core::GetInst()->GetResoulution().iH, m_pTexture->GetDC(), tCamPos.x, tCamPos.y, SRCCOPY);
	}

	for (size_t i = 0; i < m_vecTile.size(); i++)
	{
		m_vecTile[i]->Render(hDC, fDeltaTime);
	}

	//Grid를 그린다.
	POSITION	tCamPos = Camera::GetInst()->GetPos();


	for (int i = 1; i < m_iTileNumY; i++)
	{
		for (int j = 0; j < m_iTileNumX; j++)
		{
			MoveToEx(hDC, 0, i* m_iTileSizeY - tCamPos.y, NULL);
			LineTo(hDC, m_iTileNumX * m_iTileSizeX, i*m_iTileSizeY - tCamPos.y);
		}
	}

	for (int i = 1; i < m_iTileNumX; i++)
	{
		MoveToEx(hDC, i* m_iTileSizeX - tCamPos.x, 0, NULL);
		LineTo(hDC, i* m_iTileSizeX - tCamPos.x, m_iTileNumY * m_iTileSizeY);
	}

}

Stage * Stage::Clone()
{
	return new Stage(*this);
}



void Stage::Save(FILE * pFile)
{
	StaticObject::Save(pFile);

	//스테이지 정보 저장

	fwrite(&m_iTileNumX, 4, 1, pFile);
	fwrite(&m_iTileNumY, 4, 1, pFile);
	fwrite(&m_iTileSizeX, 4, 1, pFile);
	fwrite(&m_iTileSizeY, 4, 1, pFile);


	for (size_t i = 0; i < m_vecTile.size(); i++)
	{
		m_vecTile[i]->Save(pFile);
	}
}


void Stage::Load(FILE * pFile)
{
	StaticObject::Load(pFile);

	//스테이지 정보 로드

	fread(&m_iTileNumX, 4, 1, pFile);
	fread(&m_iTileNumY, 4, 1, pFile);
	fread(&m_iTileSizeX, 4, 1, pFile);
	fread(&m_iTileSizeY, 4, 1, pFile);

	ClearTile();


	for (int i = 0; i < m_iTileNumX * m_iTileNumX; i++)
	{
		Tile* pTile = Object::CreateObj<Tile>("Tile");

		pTile->Load(pFile);

		m_vecTile.push_back(pTile);
	}
}


void Stage::ClearTile()
{
	for (size_t i = 0; i < m_vecTile.size(); i++)
	{
		Object::EraseObject(m_vecTile[i]->m_strTag);
	}
	
	//Object::EraseObject();


	vector<Tile*>::iterator iter;
	vector<Tile*>::iterator iterEnd = m_vecTile.end();

	for (iter = m_vecTile.begin(); iter != iterEnd; iter++)
	{
		(*iter)->Release();
		*iter = nullptr;
	}

	m_vecTile.clear();
}
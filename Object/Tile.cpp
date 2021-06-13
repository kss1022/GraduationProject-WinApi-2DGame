#include "Tile.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Core/Camera.h"

Tile::Tile() : m_eOption(TO_NONE)
{
	m_pOptionTexture = ResourceManager::GetInst()->FindTexture("TileNone");
}

Tile::Tile(const Tile & tile) : StaticObject(tile)
{
	m_eOption = tile.m_eOption;
	m_pOptionTexture = tile.m_pOptionTexture;


	if (m_pOptionTexture)
	{
		m_pOptionTexture->AddRef();
	}
}

Tile::~Tile()
{
	if(m_pOptionTexture)
	{
	m_pOptionTexture->Release();
	m_pOptionTexture = nullptr;
	}
}



bool Tile::Init()
{
	return true;
}

void Tile::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);
}

int Tile::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);

	return 0;
}

int Tile::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);

	return 0;
}

void Tile::Collision(float fDeltaTime)
{
	StaticObject::Collision(fDeltaTime);
}

void Tile::Render(HDC hDC, float fDeltaTime)
{
	StaticObject::Render(hDC, fDeltaTime);


	POSITION	tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= Camera::GetInst()->GetPos();

	RESOLUTION tClinetRS = Camera::GetInst()->GetClinetRS();

	bool bInClinet = true;

	if (tPos.x + m_tSize.x < 0)
	{
		bInClinet = false;
	}
	else if (tPos.x > tClinetRS.iW)
	{
		bInClinet = false;
	}
	if (tPos.y + m_tSize.y < 0)
	{
		bInClinet = false;
	}
	else if (tPos.y > tClinetRS.iH)
	{
		bInClinet = false;
	}


	if (m_pOptionTexture)
	{
		if (m_pTexture && bInClinet)
		{

			POSITION tImagePos;

			tImagePos += m_tImageOffset;

			if (m_pOptionTexture->GetColorKeyEnable())
			{
				TransparentBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y), static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y),
					m_pOptionTexture->GetDC(), tImagePos.x, tImagePos.y, static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y), m_pTexture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y), static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y),
					m_pOptionTexture->GetDC(), tImagePos.x, tImagePos.y, SRCCOPY);
			}
		}
	}
}

Tile * Tile::Clone()
{
	return new Tile(*this);
}


void Tile::Save(FILE * pFile)
{
	StaticObject::Save(pFile);

	fwrite(&m_eOption, 4, 1, pFile);
}


void Tile::Load(FILE * pFile)
{
	StaticObject::Load(pFile);

	fread(&m_eOption, 4, 1, pFile);

	SetTileOption(m_eOption);
}


void Tile::SetTileOption(TILE_OPTION eOption)
{
	m_eOption = eOption;

	if (m_pOptionTexture)
	{
		m_pOptionTexture->Release();
		m_pOptionTexture = nullptr;
	}

	switch (m_eOption)
	{
	case TO_NONE:
		m_pOptionTexture = ResourceManager::GetInst()->FindTexture("TileNone");
		break;
	case TO_NOMOVE:
		m_pOptionTexture = ResourceManager::GetInst()->FindTexture("TileNoMove");
		break;
	default:
		break;
	}

}

TILE_OPTION Tile::GetTileOption() const
{
	return m_eOption;
}

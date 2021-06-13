#pragma once

#include "StaticObject.h"

class Stage : public StaticObject
{
private:
	friend class Object;
	friend class Scene;


protected:
	Stage();
	Stage(const Stage& stage);
	virtual ~Stage();

private:
	vector<class Tile*> m_vecTile;
	int		m_iTileNumX;
	int		m_iTileNumY;
	int		m_iTileSizeX;
	int		m_iTileSizeY;
	

public:
	void CreateTile(int iNumX, int iNumY, int iSIzeX, int iSizeY,
		const string& strTag ="", const wchar_t* pFIleName = nullptr,
		const string& strPathKey = TEXTURE_PATH);

	void ChangeTileTexture(const POSITION& tPos, class Texture* pTexture);
	void ChangeTileOption(const POSITION& tPos, TILE_OPTION eOption);

	int GetTileIndex(const POSITION& tPos);
	int GetTileIndex(float x, float y);
	
private:
	void ClearTile();


public:
	virtual bool Init() ;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Stage*	 Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};


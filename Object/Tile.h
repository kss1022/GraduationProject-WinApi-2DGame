#pragma once
#include "StaticObject.h"
class Tile :
	public StaticObject
{
private:
	friend class Object;
	friend class Stage;


protected:
	Tile();
	Tile(const Tile& tile);
	virtual ~Tile();


private:
	TILE_OPTION	m_eOption;
	class Texture* m_pOptionTexture;

public:
	void SetTileOption(TILE_OPTION eOption);
	TILE_OPTION GetTileOption() const;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Tile*	 Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};



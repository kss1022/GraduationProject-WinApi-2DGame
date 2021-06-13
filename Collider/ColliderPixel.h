#pragma once

#include "Collider.h"

class ColliderPixel :
	public Collider
{
private:
	friend class Collider;
	friend class Object;

protected:
	ColliderPixel();
	ColliderPixel(const ColliderPixel& collPixel);
	~ColliderPixel();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	Collider*	 Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
private:
	vector<PIXEL> m_vecPixel;
	string m_strFileName;
	string m_strPathKey;
	int m_iWidth;
	int m_iHeight;
public:
	bool SetPixelInfo(const char* pFileName, const string& strPathKey = TEXTURE_PATH);

	inline const vector<PIXEL>& GetPixel() const;
	inline int GetWidth() const;
	inline int GetHeight() const;
};




const vector<PIXEL>& ColliderPixel::GetPixel() const
{
	return m_vecPixel;
}


int ColliderPixel::GetWidth() const
{
	return m_iWidth;
}

int ColliderPixel::GetHeight() const
{
	return m_iHeight;
}

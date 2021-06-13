#pragma once

#include "../Ref.h"

class Texture : public Ref
{
private:
	friend class ResourceManager;
	Texture();
	~Texture();

private:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	BITMAP	m_tInfo;
	COLORREF	m_ColorKey;
	bool		m_bColorKeyEnable;
	
	
	wstring		m_strFileName;
	string		m_strKey;
	string		m_strPathKey;


public:
	bool LoadTexture(HINSTANCE hInst, HDC hDC,
		const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

	inline HDC GetDC() const;

	void SaveFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void Save(FILE* pFile);

	void LoadFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void Load (FILE* pFile);


	inline void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	inline void SetColorKey(COLORREF ColorKey);

	inline COLORREF GetColorKey() const;
	inline bool		GetColorKeyEnable() const;

	inline long GetWidth() const;
	inline long GetHeight() const;


};


HDC Texture::GetDC() const
{
	return 	m_hMemDC;
}








void Texture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void Texture::SetColorKey(COLORREF ColorKey)
{
	m_ColorKey = ColorKey;
	m_bColorKeyEnable = true;
}



COLORREF Texture::GetColorKey() const
{
	return m_ColorKey;
}

inline bool Texture::GetColorKeyEnable() const
{
	return m_bColorKeyEnable;
}

inline long Texture::GetWidth() const
{
	return m_tInfo.bmWidth;
}

inline long Texture::GetHeight() const
{
	return m_tInfo.bmHeight;
}


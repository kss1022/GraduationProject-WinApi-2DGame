#pragma once

#include "../Game.h"

class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();

	static ResourceManager*	m_pInst;

public:
	static ResourceManager* GetInst();
	static void DestroyInts();

private:
	unordered_map<string, class Texture*> m_mapTexture;
	HINSTANCE		m_hInst;
	HDC				m_hDC;

	class Texture*	m_pBackBuffer;

public:
	bool Init(HINSTANCE hInst, HDC hDC);


	class Texture* LoadTexture(const string& strKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

	class Texture* FindTexture(const string& strKey);

	class Texture* LoadTexture(FILE* pFile);

	class Texture* GetBackBuffer() const;
};


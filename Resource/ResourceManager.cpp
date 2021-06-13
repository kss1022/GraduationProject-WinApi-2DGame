#include "ResourceManager.h"
#include "Texture.h"


ResourceManager* ResourceManager::m_pInst = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	unordered_map<string, Texture*>::iterator iter;
	unordered_map<string, Texture*>::iterator iterEnd = m_mapTexture.end();

	for (iter = m_mapTexture.begin(); iter != iterEnd; iter++)
	{
		iter->second->Release();
		iter->second = nullptr;
	}

	m_pBackBuffer->Release();
	m_pBackBuffer = nullptr;
}

ResourceManager * ResourceManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new ResourceManager;
	}

	return	m_pInst;
}

void ResourceManager::DestroyInts()
{
	delete m_pInst;
	m_pInst = nullptr;
}







bool ResourceManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;

	//백버퍼를  불러온다,

	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");

	return true;
}

Texture * ResourceManager::LoadTexture(const string & strKey, const wchar_t * pFileName,
	const string & strPathKey)
{
	Texture* pTexture = FindTexture(strKey);


	if (pTexture)
	{
		return pTexture;
	}

	pTexture = new Texture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName, strPathKey))
	{
		pTexture->Release();
		pTexture = nullptr;

		return nullptr;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}





Texture * ResourceManager::FindTexture(const string & strKey)
{
	unordered_map<string, Texture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
	{
		return nullptr;
	}

	iter->second->AddRef();


	return iter->second;
}

Texture * ResourceManager::LoadTexture(FILE * pFile)
{

	int iLength = 0;
	char strKey[MAX_PATH] = {};
	char strPathKey[MAX_PATH] = {};
	wchar_t strFileName[MAX_PATH] = {};

	//key 로드	
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strKey, 1, iLength, pFile);
	strKey[iLength] = 0;

	//FileName 로드
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strFileName, 2, iLength, pFile);
	strFileName[iLength] = 0;

	//PathKey 로드	
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strPathKey, 1, iLength, pFile);
	strPathKey[iLength] = 0;


	bool bColorKey = false;
	COLORREF	dwColorKey = 0;
	fread(&bColorKey, 1, 1, pFile);
	fread(&dwColorKey, sizeof(COLORREF), 1, pFile);



	Texture* pTexture = ResourceManager::GetInst()->LoadTexture(strKey, strFileName, strPathKey);

	if (pTexture && bColorKey)
	{
		pTexture->SetColorKey(dwColorKey);
	}

	return pTexture;
}



Texture * ResourceManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();
	return m_pBackBuffer;
}

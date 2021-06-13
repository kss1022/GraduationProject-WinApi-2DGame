#include "Texture.h"
#include "../Core/PathManager.h"
#include "./ResourceManager.h"
Texture::Texture() : m_hMemDC(nullptr), m_hBitmap(nullptr), m_hOldBitmap(nullptr),
m_bColorKeyEnable(false), m_ColorKey(RGB(255, 0, 255))
{
}

Texture::~Texture()
{
	//기존에 지정되 있던 도구를 다시 지정해준다.
	SelectObject(m_hMemDC, m_hOldBitmap);

	//Bitmap을 지워준다
	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);
}

bool Texture::LoadTexture(HINSTANCE hInst, HDC hDC,
	const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	m_strFileName = pFileName;
	m_strKey = strKey;;
	m_strPathKey = strPathKey;


	//메모리 DC를 만들어준다
	m_hMemDC = CreateCompatibleDC(hDC);

	//전체 경로를 만들어준다
	const wchar_t* pPath = PathManager::GetInst()->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
	{
		strPath = pPath;
	}


	strPath += pFileName;





	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//위에서 만들어준 비트맵 도구를 DC에 지정한다
	//지정할떄 반환되는 값을 DC에 기본으로 지정되어 있던 도구가 반환된다

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}



void Texture::SaveFromPath(const char * pFileName, const string & strPathKey)
{
}

void Texture::Save(FILE * pFile)
{
	
	//key 저장	
	int iLength = m_strKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, iLength, pFile);

	//FileName저장
	iLength = m_strFileName.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, iLength, pFile);

	//PathKey저장
	iLength = m_strPathKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strPathKey.c_str(), 1, iLength, pFile);

	//ColorKey
	fwrite(&m_bColorKeyEnable, 1, 1, pFile);
	fwrite(&m_ColorKey, sizeof(COLORREF), 1, pFile);

}

void Texture::LoadFromPath(const char * pFileName, const string & strPathKey)
{
}

void Texture::Load(FILE * pFile)
{	/*
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
	strKey[iLength] = 0;



	//PathKey 로드
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strPathKey, 1, iLength, pFile);
	strKey[iLength] = 0;

	ResourceManager::GetInst()->LoadTexture(strKey, strFileName, strPathKey);

	fwrite(&m_bColorKeyEnable, 1, 1, pFile);
	fwrite(&m_ColorKey, sizeof(COLORREF), 1, pFile);
	*/
}


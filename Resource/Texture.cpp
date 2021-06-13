#include "Texture.h"
#include "../Core/PathManager.h"
#include "./ResourceManager.h"
Texture::Texture() : m_hMemDC(nullptr), m_hBitmap(nullptr), m_hOldBitmap(nullptr),
m_bColorKeyEnable(false), m_ColorKey(RGB(255, 0, 255))
{
}

Texture::~Texture()
{
	//������ ������ �ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);

	//Bitmap�� �����ش�
	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);
}

bool Texture::LoadTexture(HINSTANCE hInst, HDC hDC,
	const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	m_strFileName = pFileName;
	m_strKey = strKey;;
	m_strPathKey = strPathKey;


	//�޸� DC�� ������ش�
	m_hMemDC = CreateCompatibleDC(hDC);

	//��ü ��θ� ������ش�
	const wchar_t* pPath = PathManager::GetInst()->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
	{
		strPath = pPath;
	}


	strPath += pFileName;





	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//������ ������� ��Ʈ�� ������ DC�� �����Ѵ�
	//�����ҋ� ��ȯ�Ǵ� ���� DC�� �⺻���� �����Ǿ� �ִ� ������ ��ȯ�ȴ�

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}



void Texture::SaveFromPath(const char * pFileName, const string & strPathKey)
{
}

void Texture::Save(FILE * pFile)
{
	
	//key ����	
	int iLength = m_strKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, iLength, pFile);

	//FileName����
	iLength = m_strFileName.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, iLength, pFile);

	//PathKey����
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

	//key �ε�	
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strKey, 1, iLength, pFile);
	strKey[iLength] = 0;


	//FileName �ε�
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strFileName, 2, iLength, pFile);
	strKey[iLength] = 0;



	//PathKey �ε�
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strPathKey, 1, iLength, pFile);
	strKey[iLength] = 0;

	ResourceManager::GetInst()->LoadTexture(strKey, strFileName, strPathKey);

	fwrite(&m_bColorKeyEnable, 1, 1, pFile);
	fwrite(&m_ColorKey, sizeof(COLORREF), 1, pFile);
	*/
}


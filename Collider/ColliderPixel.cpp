#include "ColliderPixel.h"
#include "../Object/Object.h"
#include "ColliderSphere.h"
#include "ColliderReact.h"
#include "ColliderPoint.h"
#include "../Core/PathManager.h"

ColliderPixel::ColliderPixel()
{
	m_eCollType = CT_PIXEL;
	m_iWidth = 0;
	m_iHeight = 0;
}

ColliderPixel::ColliderPixel(const ColliderPixel & collPixel)
{
	//	m_tInfo = collSphere.m_tInfo;
	m_eCollType = collPixel.m_eCollType;

	m_iWidth = collPixel.m_iWidth;
	m_iHeight = collPixel.m_iHeight;
}

ColliderPixel::~ColliderPixel()
{
}

bool ColliderPixel::Init()
{
	return true;
}

void ColliderPixel::Input(float fDeltaTime)
{
}

int ColliderPixel::Update(float fDeltaTime)
{
	return 0;
}

int ColliderPixel::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool ColliderPixel::Collision(Collider * pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_REACT:
		return CollisionReactToPixel(((ColliderReact*)pDest)->GetWorldInfo(),
			m_vecPixel, m_iWidth, m_iHeight);
		break;
	case CT_SPEARE:
		return CollisionSphereToPixel(((ColliderSphere*)pDest)->GetWorldInfo(),
			m_vecPixel, m_iWidth, m_iHeight);
		break;
	case CT_POINT:
		return CollisionPixelToPoint(m_vecPixel, m_iWidth, m_iHeight,
			((ColliderPoint*)pDest)->GetPoint());
		break;
	default:
		break;
	}
	return false;
}

void ColliderPixel::Render(HDC hDC, float fDeltaTime)
{
}

Collider * ColliderPixel::Clone()
{
	return new ColliderPixel(*this);
}

void ColliderPixel::Save(FILE * pFile)
{
	Collider::Save(pFile);

	//파일 이름저장
	int iLength = m_strFileName.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 1, iLength, pFile);

	//파일 경로저장
	iLength = m_strPathKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strPathKey.c_str(), 1, iLength, pFile);
}

void ColliderPixel::Load(FILE * pFile)
{
	Collider::Load(pFile);
}

bool ColliderPixel::SetPixelInfo(const char * pFileName, const string & strPathKey)
{
	m_strFileName = pFileName;
	m_strPathKey = strPathKey;

	const char* pPath = PathManager::GetInst()->FindPathMultiByte(strPathKey);
	string strPath;

	if (pPath)
	{
		strPath = pPath;
	}

	strPath += pFileName;

	FILE* pFile = nullptr;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (!pFile)
	{
		return false;
	}

	BITMAPFILEHEADER	fh;
	BITMAPINFOHEADER	ih;


	fread(&fh, sizeof(fh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	m_iWidth = ih.biWidth;
	m_iHeight = ih.biHeight;

	m_vecPixel.clear();

	m_vecPixel.resize(m_iWidth * m_iHeight);

	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	PIXEL* pPixelArr = new PIXEL[m_iWidth];

	//위아래를 반전 시켜줌


	for (int i = 0; i < m_iHeight / 2; i++)
	{
		//현재 인덱스의 픽셀 한줄 저장

		memcpy(pPixelArr, &m_vecPixel[i * m_iWidth], sizeof(PIXEL)  * m_iWidth);


		memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHeight - i - 1) * m_iWidth], sizeof(PIXEL)  * m_iWidth);

		memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelArr, sizeof(PIXEL)  * m_iWidth);

	}

	delete[] pPixelArr;

	fclose(pFile);

	
	fopen_s(&pFile, "test.bmp", "wb");

	fwrite(&fh, sizeof(fh), 1, pFile);
	fwrite(&ih, sizeof(ih), 1, pFile);
	fwrite(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	fclose(pFile);
	
	return true;
}



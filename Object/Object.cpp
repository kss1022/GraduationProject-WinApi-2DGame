#include "Object.h"
#include "../Scene/Scene.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Collider/Collider.h"
#include "../Core/PathManager.h"
#include"../Collider/ColliderReact.h"
#include"../Collider/ColliderSphere.h"
#include"../Collider/ColliderPixel.h"
#include"../Collider/ColliderPoint.h"

list<Object*> Object::m_ObjectList;

Object::Object() : m_pTexture(nullptr), m_bIsPhysics(false), m_fGravityTime(0.f)
{
}

Object::Object(const Object & obj)
{
	*this = obj;
	m_iRef = 1;

	if (obj.m_pAnimation)
	{
		m_pAnimation = obj.m_pAnimation->Clone();
	}

	m_fGravityTime = 0.f;

	if (m_pTexture)
	{
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();

	list<Collider*>::const_iterator iter;
	list<Collider*>::const_iterator iterEnd = obj.m_ColliderList.end();

	for (iter = obj.m_ColliderList.begin(); iter != iterEnd; iter++)
	{
		Collider* pColl = (*iter)->Clone();

		pColl->SetObject(this);

		m_ColliderList.push_back(pColl);
	}
}

Object::~Object()
{
	if (m_pAnimation)
	{
		m_pAnimation->Release();
		m_pAnimation = nullptr;
	}

	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; iter++)
	{
		delete *iter;
		*iter = nullptr;
	}



	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

}


void Object::AddObject(Object * pObj)
{
	pObj->AddRef();
	m_ObjectList.push_back(pObj);
}


Object * Object::FindObjet(const string & strTag)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; iter++)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}


	return nullptr;
}

void Object::EraseObject(Object * pObj)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd;)
	{
		if (*iter == pObj)
		{
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else iter++;
	}


}

void Object::EraseObject(const string & strTag)
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ObjectList.erase(iter);
			iterEnd = m_ObjectList.end();
		}
		else iter++;
	}


}

void Object::EraseObject()
{
	list<Object*>::iterator iter;
	list<Object*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; iter++)
	{
		(*iter)->Release();
		*iter = nullptr;
	}

	m_ObjectList.clear();
}


void Object::SetTexture(Texture * pTextrue)
{
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	m_pTexture = pTextrue;

	if (pTextrue)
	{
		pTextrue->AddRef();
	}
}

void Object::SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	m_pTexture = ResourceManager::GetInst()->LoadTexture(strKey, pFileName, strPathKey);
}

void Object::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_pTexture->SetColorKey(r, g, b);
}

bool Object::CheckCollider()
{
	return !m_ColliderList.empty();
}


Collider * Object::GetCollider(const string & strTag)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; iter++)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return  *iter;
		}
	}

	return nullptr;
}


Animation * Object::CreateAnimation(const string & strTag)
{
	if (m_pAnimation)
	{
		m_pAnimation->Release();
	}

	m_pAnimation = new Animation;

	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObject(this);


	if (!m_pAnimation->Init())
	{
		m_pAnimation->Release();
		m_pAnimation = nullptr;

		return nullptr;
	}

	m_pAnimation->AddRef();

	return m_pAnimation;
}

bool Object::AddAnimationClip(const string & strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const string & strTextKey, const wchar_t * pFileName, const string & strPathKey)
{
	if (!m_pAnimation)
	{
		return false;
	}

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime,
		iFrameMaxX, iFrameMaxY, iStartX, iStartY, iLengthX, iLengthY, fOptionLimitTime,
		strTextKey, pFileName, strPathKey);

	return true;
}

bool Object::AddAnimationClip(const string & strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const string & strTextKey, const vector<wstring>& vecFileName, const string & strPathKey)
{
	if (!m_pAnimation)
	{
		return false;
	}

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime,
		iFrameMaxX, iFrameMaxY, iStartX, iStartY, iLengthX, iLengthY, fOptionLimitTime,
		strTextKey, vecFileName, strPathKey);

	return true;
}

void Object::SetAnimationClipColorKey(const string & strClip, unsigned char r, unsigned char g, unsigned char b)
{
	if (m_pAnimation)
	{
		m_pAnimation->SetClipColorKey(strClip, r, g, b);
	}
}

bool Object::Init()
{
	return true;
}

void Object::Input(float fDeltaTime)
{
}

int Object::Update(float fDeltaTime)
{


	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Input(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else iter++;
	}

	if (m_pAnimation)
	{
		m_pAnimation->Update(fDeltaTime);
	}

	return 0;

}

int Object::LateUpdate(float fDeltaTime)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);


		if (!(*iter)->GetLife())
		{
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else iter++;
	}
	return 0;
}

void Object::Collision(float fDeltaTime)
{
}

void Object::Render(HDC hDC, float fDeltaTime)
{
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



	if (m_pTexture && bInClinet)
	{

		POSITION tImagePos;

		if (m_pAnimation)
		{
			ANIMATIONCLIP* pClip = m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS)
			{
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y), static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y),
				m_pTexture->GetDC(), tImagePos.x, tImagePos.y, static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y), m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, static_cast<int>(tPos.x), static_cast<int>(tPos.y), static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y),
				m_pTexture->GetDC(), tImagePos.x, tImagePos.y, SRCCOPY);
		}
	}


	if (bInClinet)
	{
		list<Collider*>::iterator iter;
		list<Collider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd;)
		{
			if (!(*iter)->GetEnable())
			{
				iter++;
				continue;
			}

			(*iter)->Render(hDC, fDeltaTime);


			if (!(*iter)->GetLife())
			{
				(*iter)->Release();
				*iter = nullptr;

				iter = m_ColliderList.erase(iter);
				iterEnd = m_ColliderList.end();
			}
			else iter++;
		}
	}
}

void Object::SaveFromPath(const char * pFileName, const string & strPathKey)
{
	const char* pPath = PathManager::GetInst()->FindPathMultiByte(DATA_PATH);

	string strFullPath;

	if (pPath)
	{
		strFullPath = pPath;
	}

	strFullPath += pFileName;

	SaveFromFullPath(strFullPath.c_str());
}

void Object::Save(FILE * pFile)
{
	//Tag정보 저장
	int iLength = m_strTag.length();

	//Tag길이 저장
	fwrite(&iLength, 4, 1, pFile);

	//Tag 문자열 저장
	fwrite(m_strTag.c_str(), 1, iLength, pFile);


	//물리 사용여부 저장
	fwrite(&m_bIsPhysics, 1, 1, pFile);

	//위치 저장
	fwrite(&m_tPos, sizeof(m_tPos), 1, pFile);

	//크기 저장
	fwrite(&m_tSize, sizeof(m_tSize), 1, pFile);

	//ImageOffset 저장
	fwrite(&m_tImageOffset, sizeof(m_tImageOffset), 1, pFile);

	//Pivot 저장
	fwrite(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	//Texture 저장
	bool bTexture = false;
	if (m_pTexture)
	{
		bTexture = true;
		fwrite(&bTexture, 1, 1, pFile);
		m_pTexture->Save(pFile);
	}
	else
	{
		fwrite(&bTexture, 1, 1, pFile);
	}

	//충돌체 저장
	iLength = m_ColliderList.size();
	fwrite(&iLength, 4, 1, pFile);

	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; iter++)
	{
		COLLIDER_TYPE eType = (*iter)->GetColliderType();
		fwrite(&eType, 4, 1, pFile);
		(*iter)->Save(pFile);
	}


	//애니메이션 저장
	bool bAnimation = false;
	if (m_pAnimation)
	{
		bAnimation = true;
		fwrite(&bAnimation, 1, 1, pFile);
		m_pAnimation->Save(pFile);
	}
	else
	{
		fwrite(&bAnimation, 1, 1, pFile);
	}

}

void Object::SaveFromFullPath(const char * pFullPah)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPah, "wb");

	if (pFile)
	{
		Save(pFile);
		fclose(pFile);
	}
}

void Object::LoadFromPath(const char * pFileName, const string & strPathKey)
{
	const char* pPath = PathManager::GetInst()->FindPathMultiByte(DATA_PATH);

	string strFullPath;

	if (pPath)
	{
		strFullPath = pPath;
	}

	strFullPath += pFileName;

	LoadFromFullPath(strFullPath.c_str());
}

void Object::LoadFromFullPath(const char * pFullPah)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPah, "rb");

	if (pFile)
	{
		Load(pFile);
		fclose(pFile);
	}
}

void Object::Load(FILE * pFile)
{	//Tag정보 로드
	int iLength = 0;
	char	strText[MAX_PATH] = {};

	//Tag길이 로드
	fread(&iLength, 4, 1, pFile);

	//Tag 문자열 로드
	fread(strText, 1, iLength, pFile);
	strText[iLength] = 0;
	m_strTag = strText;


	//물리 사용여부 로드
	fread(&m_bIsPhysics, 1, 1, pFile);

	//위치 로드
	fread(&m_tPos, sizeof(m_tPos), 1, pFile);

	//크기 로드
	fread(&m_tSize, sizeof(m_tSize), 1, pFile);

	//ImageOffset 로드
	fread(&m_tImageOffset, sizeof(m_tImageOffset), 1, pFile);

	//Pivot 로드
	fread(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	//Texture 로드
	bool bTexture = false;
	fread(&bTexture, 1, 1, pFile);

	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	if (bTexture)
	{
		m_pTexture =ResourceManager::GetInst()->LoadTexture(pFile);
	}

	//충돌체 로드
	iLength = m_ColliderList.size();
	fread(&iLength, 4, 1, pFile);

	for (int i = 0; i < iLength; i++)
	{
		COLLIDER_TYPE eType;
		fread(&eType, 4, 1, pFile);

		Collider* pCollier = nullptr;

		switch (eType)
		{
		case CT_REACT:
			pCollier = AddCollider<ColliderReact>("");
			break;
		case CT_SPEARE:
			pCollier = AddCollider<ColliderSphere>("");
			break;
		case CT_POINT:
			pCollier = AddCollider<ColliderPoint>("");
			break;
		case CT_PIXEL:
			pCollier = AddCollider<ColliderPixel>("");
			break;
		case CT_END:
			break;
		default:
			break;
		}

		pCollier->Load(pFile);

		pCollier->Release();
		pCollier = nullptr;
	}


	//애니메이션 로드
	bool bAnimation = false;
	fread(&bAnimation, 1, 1, pFile);


	if (m_pAnimation)
	{
		m_pAnimation->Release();
		m_pAnimation = nullptr;
	}

	if (bAnimation)
	{
		m_pAnimation = new Animation;
		
		m_pAnimation->Init();
		m_pAnimation->Load(pFile);
	}
}




Object* Object::CreateCloneObject(const string & strPrototypeKey,
	const string& strTag, SCENE_CREATE sc, Layer* pLayer)
{
	Object* pPrototype = Scene::FindPrototype(strPrototypeKey, sc);

	if (!pPrototype)
	{
		return nullptr;
	}

	Object* pObj = pPrototype->Clone();

	pObj->SetTag(strTag);

	if (pLayer)
	{
		pLayer->AddObject(pObj);
	}

	AddObject(pObj);

	return pObj;
}
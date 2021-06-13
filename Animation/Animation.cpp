#include "Animation.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Object/Object.h"
Animation::Animation() : m_pCurClip(nullptr), m_bMotionEnd(false)
{
}

Animation::Animation(const Animation & animaiton)
{

	*this = animaiton;

	m_bMotionEnd = animaiton.m_bMotionEnd;

	m_mapClip.clear();

	unordered_map<string, ANIMATIONCLIP*>::const_iterator iter;
	unordered_map<string, ANIMATIONCLIP*>::const_iterator iterEnd = animaiton.m_mapClip.end();

	for (iter = animaiton.m_mapClip.begin(); iter != iterEnd; iter++)
	{
		ANIMATIONCLIP* pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;

		for (size_t i = 0; i < pClip->vecTexture.size(); i++)
		{
			pClip->vecTexture[i]->AddRef();
			m_mapClip.insert(make_pair(iter->first, pClip));
		}
	}
	/*
	m_pCurClip = nullptr;

	m_strDefaultClip = "";
	SetCurrentClip(animaiton.m_strCurClip);
	*/
}

Animation::~Animation()
{

	unordered_map<string, ANIMATIONCLIP*>::iterator iter;
	unordered_map<string, ANIMATIONCLIP*>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; iter++)
	{
		for (size_t i = 0; i < iter->second->vecTexture.size(); i++)
		{
			(iter->second->vecTexture[i])->Release();
			(iter->second->vecTexture[i]) = nullptr;
		}
		delete iter->second;
		iter->second = nullptr;
	}


	m_mapClip.clear();
}

bool Animation::AddClip(const string & strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
	float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
	int iLengthX, int iLengthY, float fOptionLimitTime, const string & strTextKey,
	const wchar_t* pFileName, const string & strPathKey)
{
	ANIMATIONCLIP* pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iFrameMaxX = iFrameMaxX;
	pClip->iFrameMaxY = iFrameMaxY;
	pClip->iStartX = iStartX;
	pClip->iStartY = iStartY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;
	pClip->fAnimationFrameTime = fAnimationLimitTime / (iLengthX * iLengthY);

	Texture* pTexture = ResourceManager::GetInst()->LoadTexture(strTextKey,
		pFileName, strPathKey);



	pClip->tFrameSize.x = pTexture->GetWidth() / iFrameMaxX;
	pClip->tFrameSize.y = pTexture->GetHeight() / iFrameMaxY;

	pClip->vecTexture.push_back(pTexture);

	pClip->fAnimationTime = 0.f;
	pClip->iFrameX = iStartX;
	pClip->iFrameY = iStartY;
	pClip->fOptionTime = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));


	if (m_strDefaultClip.empty())
	{
		SetCDefaultClip(strName);
	}

	if (m_strCurClip.empty())
	{
		SetCurrentClip(strName);
	}

	return true;
}

bool Animation::AddClip(const string & strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const string & strTextKey, const vector<wstring>& vecFileName, const string & strPathKey)
{
	ANIMATIONCLIP* pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iFrameMaxX = iFrameMaxX;
	pClip->iFrameMaxY = iFrameMaxY;
	pClip->iStartX = iStartX;
	pClip->iStartY = iStartY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;
	pClip->fAnimationFrameTime = fAnimationLimitTime / (iLengthX * iLengthY);

	for (size_t i = 0; i < vecFileName.size(); i++)
	{
		char strKey[256] = {};
		sprintf_s(strKey, "%s%d", strTextKey.c_str(), i + 1);

		Texture* pTexture = ResourceManager::GetInst()->LoadTexture(strKey,
			vecFileName[i].c_str(), strPathKey);

		pClip->vecTexture.push_back(pTexture);
	}


	pClip->tFrameSize.x = pClip->vecTexture[0]->GetWidth();
	pClip->tFrameSize.y = pClip->vecTexture[0]->GetHeight();

	pClip->fAnimationTime = 0.f;
	pClip->iFrameX = iStartX;
	pClip->iFrameY = iStartY;
	pClip->fOptionTime = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));


	if (m_strDefaultClip.empty())
	{
		SetCDefaultClip(strName);
	}

	if (m_strCurClip.empty())
	{
		SetCurrentClip(strName);
	}

	return true;
}


void Animation::ChangeClip(const string & strClip)
{
	if (m_strCurClip == strClip)
	{
		return;
	}

	m_strCurClip = strClip;

	if (m_pCurClip)
	{
		m_pCurClip->iFrameX = m_pCurClip->iStartX;
		m_pCurClip->iFrameY = m_pCurClip->iStartY;

		m_pCurClip->fAnimationTime = 0.f;
		m_pCurClip->fOptionTime = 0.f;
	}

	m_pCurClip = FIndClip(strClip);


	m_pObject->SetTexture(m_pCurClip->vecTexture[0]);


	if (m_pCurClip->eType == AT_ATLAS)
	{
		m_pObject->SetTexture(m_pCurClip->vecTexture[0]);
	}
	else if (m_pCurClip->eType == AT_FRAME)
	{
		m_pObject->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameX]);
	}

}



void Animation::ChangeClip(float fAnimationLimitTime, int iStartX, int iStartY, int iLengthX, int iLengthY)
{
	m_pCurClip->fAnimationTime = 0.f;
	m_pCurClip->fOptionTime = 0.f;


	m_pCurClip->fAnimationLimitTime = fAnimationLimitTime;
	m_pCurClip->iStartX = iStartX;
	m_pCurClip->iStartY = iStartY;
	m_pCurClip->iLengthX = iLengthX;
	m_pCurClip->iLengthY = iLengthY;


	m_pCurClip->iFrameX = m_pCurClip->iStartX;
	m_pCurClip->iFrameY = m_pCurClip->iStartY;

	m_pObject->SetTexture(m_pCurClip->vecTexture[0]);

}



ANIMATIONCLIP * Animation::FIndClip(const string & strName)
{
	unordered_map<string, ANIMATIONCLIP*>::iterator iter = m_mapClip.find(strName);

	if (iter == m_mapClip.end())
	{
		return nullptr;
	}

	return iter->second;
}


void Animation::SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	ANIMATIONCLIP* pClip = FIndClip(strClip);

	if (!pClip)
	{
		return;
	}

	for (size_t i = 0; i < pClip->vecTexture.size(); i++)
	{
		pClip->vecTexture[i]->SetColorKey(r, g, b);
	}
}

void Animation::ReturenClip()
{
	ChangeClip(m_strDefaultClip);
}


bool Animation::Init()
{
	return true;
}


bool Animation::Update(float fDeltaTime)
{
	m_bMotionEnd = false;

	m_pCurClip->fAnimationTime += fDeltaTime;

	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFrameTime)
	{
		m_pCurClip->fAnimationTime -= m_pCurClip->fAnimationFrameTime;

		++m_pCurClip->iFrameX;



		if (m_pCurClip->iFrameX - m_pCurClip->iStartX == m_pCurClip->iLengthX)
		{
			m_pCurClip->iFrameX = m_pCurClip->iStartX;
			++m_pCurClip->iFrameY;


			if (m_pCurClip->iFrameY - m_pCurClip->iStartY == m_pCurClip->iLengthY)
			{
				m_pCurClip->iFrameY = m_pCurClip->iStartY;

				if (m_pCurClip->eType == AT_FRAME)
				{
					m_pObject->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameX]);
				}

				m_bMotionEnd = true;

				switch (m_pCurClip->eOption)
				{
				case AO_ONCE_RETURN:
					ChangeClip(m_strDefaultClip);
					break;
				case AO_ONCE_DESTROY:
					m_pObject->Die();
					break;
				case AO_TIME_RETURN:
					break;
				case AO_TIME_DESTROY:
					break;
				case AO_LOPE:
					break;
				}
			}

		}
		else
		{
			if (m_pCurClip->eType == AT_FRAME)
			{
				m_pObject->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameX]);
			}
		}
	}

	return true;
}



Animation * Animation::Clone()
{
	return new Animation(*this);
}



void Animation::Save(FILE * pFile)
{
	//Tag정보 저장
	int iLength = m_strTag.length();

	//Tag길이 저장
	fwrite(&iLength, 4, 1, pFile);

	//Tag 문자열 저장
	fwrite(m_strTag.c_str(), 1, iLength, pFile);


	int iCount = m_mapClip.size();
	fwrite(&iCount, 4, 1, pFile);

	unordered_map<string, ANIMATIONCLIP*>::iterator iter;
	unordered_map<string, ANIMATIONCLIP*>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; iter++)
	{
		fwrite(&iter->second->eType, 4, 1, pFile);
		fwrite(&iter->second->eOption, 4, 1, pFile);

		iCount = iter->second->vecTexture.size();
		fwrite(&iCount, 4, 1, pFile);

		for (size_t i = 0; i < iCount; i++)
		{
			iter->second->vecTexture[i]->Save(pFile);
		}
		fwrite(&iter->second->fAnimationFrameTime, 4, 1, pFile);
		fwrite(&iter->second->fAnimationLimitTime, 4, 1, pFile);
		fwrite(&iter->second->iFrameMaxX, 4, 1, pFile);
		fwrite(&iter->second->iFrameMaxY, 4, 1, pFile);
		fwrite(&iter->second->iStartX, 4, 1, pFile);
		fwrite(&iter->second->iStartY, 4, 1, pFile);
		fwrite(&iter->second->iLengthX, 4, 1, pFile);
		fwrite(&iter->second->iLengthY, 4, 1, pFile);
		fwrite(&iter->second->iLengthY, 4, 1, pFile);
		fwrite(&iter->second->fOptionLimitTime, 8, 1, pFile);
		fwrite(&iter->second->tFrameSize, sizeof(_SIZE), 1, pFile);
	}


	//CurClip정보 저장
	iLength = m_strCurClip.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strCurClip.c_str(), 1, iLength, pFile);


	//DefaultClip정보 저장
	iLength = m_strDefaultClip.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strDefaultClip.c_str(), 1, iLength, pFile);

}

void Animation::Load(FILE * pFile)
{
}


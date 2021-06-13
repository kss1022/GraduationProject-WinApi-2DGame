#include "SoundManager.h"
#include "../Core/PathManager.h"

SoundManager* SoundManager::m_pInst = nullptr;

SoundManager::SoundManager() : 
	m_pSystem(nullptr)
{
}

SoundManager::~SoundManager() 
{
	unordered_map<string, SOUNDINFO*>::iterator iter;
	unordered_map<string, SOUNDINFO*>::iterator iterEnd = m_mapSound.end();
	
	for (iter = m_mapSound.begin(); iter != iterEnd; iter++)
	{
		iter->second->pSound->release();
		
		delete iter->second;
		iter->second = nullptr;
	}

	m_pSystem->close();
	m_pSystem->release();
}

SoundManager * SoundManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new SoundManager;
	}
	return m_pInst;
}

void SoundManager::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

bool SoundManager::Init()
{
	FMOD::System_Create(&m_pSystem);

	m_pSystem->init(10, FMOD_INIT_NORMAL, nullptr);

	return true;
}

bool SoundManager::LoadSound(const string & strKey, bool bLoop, const char * pFileName, const string & strPathKey)
{
	if (FindSoundInfo(strKey))
	{
		return true;
	}
	
	/*
	const char* pPath = PathManager::GetInst()->FindPathMultiByte(strPathKey);

	string strFullPath;

	if (pPath)
	{
		strFullPath = pPath;
	}
	
	strFullPath += pFileName;
	
	*/




#ifdef _DEBUG
	//콘솔창을 생성시켜주는 함수이다
	string strFullPath = "Bin\\Sound\\";
	strFullPath += pFileName;
#else
	string strFullPath = "Sound\\";
	strFullPath += pFileName;
#endif // _DEBUG
	

	FMOD_MODE eMode = FMOD_LOOP_NORMAL;

	if (!bLoop)
	{
		eMode = PDC_MODE_DEFAULT;
	}

	SOUNDINFO* pSoundInfo = new  SOUNDINFO;

	pSoundInfo->bLoop = bLoop;
	
	m_pSystem->createSound(strFullPath.c_str(),eMode, NULL ,&(pSoundInfo->pSound));

	m_mapSound.insert(make_pair(strKey, pSoundInfo));

	return true;
}

bool SoundManager::Play(const string & strKey)
{
	SOUNDINFO* pSound = FindSoundInfo(strKey);

	if (!pSound)
	{
		return false;
	}

	m_pSystem->update();
	
	SOUND_TYPE eChannel = ST_BGM;

	if (!pSound->bLoop)
	{
		eChannel = ST_EFFECT;
	}

	m_pSystem->playSound(pSound->pSound, NULL, false, &m_pChannel[eChannel]);

	return true;
}

bool SoundManager::Stop(SOUND_TYPE eChannel)
{
	m_pChannel[eChannel]->stop();

	return true;
}

bool SoundManager::Volume(SOUND_TYPE eChannel, float fVolume)
{
	m_pChannel[eChannel]->setVolume(fVolume);

	return true;
}


SOUNDINFO * SoundManager::FindSoundInfo(const string & strKey)
{
	unordered_map<string, SOUNDINFO*>::iterator iter = m_mapSound.find(strKey);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return iter->second;
}



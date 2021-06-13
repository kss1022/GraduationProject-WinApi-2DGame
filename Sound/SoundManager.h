#pragma once
#include "../Game.h"

using namespace FMOD;

typedef struct _tagSoundInfo
{
	FMOD::Sound* pSound;
	bool	bLoop;
}SOUNDINFO;


enum SOUND_TYPE
{
	ST_BGM,
	ST_EFFECT,
	ST_END
};

class SoundManager
{

private:
	SoundManager();
	~SoundManager();

	static SoundManager*	m_pInst;
public:
	static SoundManager*	GetInst();
	static void				DestroyInst();


private:
	FMOD::System* m_pSystem;
	FMOD::Channel* m_pChannel[ST_END];
	unordered_map<string, SOUNDINFO*> m_mapSound;
public:
	bool Init();
	bool LoadSound(const string& strKey, bool bLoop, 
		const char* pFileName, const string& strPathKey = SOUND_PATH);
	
	bool Play(const string& strKey);
	bool Stop(SOUND_TYPE eChannel);
	bool Volume(SOUND_TYPE eChannel, float fVolume);

private:
	SOUNDINFO*	FindSoundInfo(const string& strKey);
};


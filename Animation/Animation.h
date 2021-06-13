#pragma once
#include "../Ref.h"
#include "../Game.h"

class Animation :
	public Ref
{
private:
	friend class Object;

private:
	Animation();
	Animation(const Animation& animaiton);
	~Animation();

private:
	unordered_map<string, ANIMATIONCLIP*> m_mapClip;
	ANIMATIONCLIP*	m_pCurClip;
	string			m_strCurClip;
	string			m_strDefaultClip;
	class Object*	m_pObject;
	bool			m_bMotionEnd;
public:
	bool AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY,
		int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTextKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

	bool AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY,
		int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTextKey, const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);



	inline void SetObject(class Object* pObject);
	inline void SetCurrentClip(const string& strCurClip);
	inline void SetCDefaultClip(const string& strDefaultClip);


	void ChangeClip(const string& strClip);
	void ChangeClip(float fAnimationLimitTime,int iStartX, int iStartY, int iLengthX, int iLengthY);
	inline ANIMATIONCLIP* GetCurrentClip() const;
	inline string  GetCurrentStrClip() const;
	inline string  GetDefaultStrClip() const;

	inline bool	GetMotionEnd() const;
	inline void	SetMotionEnd(bool bMotionEnd);

	void SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);
	void ReturenClip();
private:
	ANIMATIONCLIP* FIndClip(const string& strName);

public:
	bool	Init();
	bool	Update(float fDeltaTime);
	Animation*	Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

void Animation::SetObject(Object * pObject)
{
	m_pObject = pObject;
}

void Animation::SetCurrentClip(const string & strCurClip)
{
	ChangeClip(strCurClip);
}

void Animation::SetCDefaultClip(const string & strDefaultClip)
{
	m_strDefaultClip = strDefaultClip;
}


ANIMATIONCLIP * Animation::GetCurrentClip() const
{
	return m_pCurClip;
}


string  Animation::GetCurrentStrClip() const
{
	return m_strCurClip;
}

string Animation::GetDefaultStrClip() const
{
	return m_strDefaultClip;
}



inline bool Animation::GetMotionEnd() const
{
	return m_bMotionEnd;
}

inline void Animation::SetMotionEnd(bool bMotionEnd) 
{
	m_bMotionEnd = bMotionEnd;
}
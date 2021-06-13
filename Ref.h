#pragma once

#include "Game.h"

class Ref
{
protected:
	Ref();
	virtual ~Ref() = 0;

	int		m_iRef;
	bool	m_bEnable;
	bool	m_bLife;
	string	m_strTag;

public:
	void AddRef();
	int Release();

	inline void SetEnable(bool bEnable);
	inline void Die();
	
	inline bool GetEnable() const;
	inline bool GetLife() const;

	inline void SetTag(const string& strTag);
	inline string GetTag() const;
};

void Ref::SetEnable(bool bEnable) 
{
	m_bEnable = bEnable;
}

void Ref::Die()
{
	m_bLife = false;
} 

bool Ref::GetEnable() const
{
	return m_bEnable;
}


bool Ref::GetLife() const
{
	return m_bLife;
}

inline void Ref::SetTag(const string& strTag)
{
	m_strTag = strTag;
}

inline string Ref::GetTag() const
{
	return m_strTag;
}

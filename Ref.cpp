#include "Ref.h"

Ref::Ref() : m_iRef(1), m_bEnable(true), m_bLife(true)
{
}

Ref::~Ref()
{
}

void Ref::AddRef()
{
	++m_iRef;
}

int Ref::Release()
{
	--m_iRef;

	if (m_iRef == 0)
	{
		delete this;
		return 0;
	}

	return m_iRef;
}

#include "StaticObject.h"

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(const StaticObject & obj) : Object(obj)
{
}

StaticObject::~StaticObject()
{
}



bool StaticObject::Init()
{
	return true;
}

void StaticObject::Input(float fDeltaTime)
{
	Object::Input(fDeltaTime);
}

int StaticObject::Update(float fDeltaTime)
{
	Object::Update(fDeltaTime);
	return 0;
}

int StaticObject::LateUpdate(float fDeltaTime)
{
	Object::LateUpdate(fDeltaTime);
	return 0;
}

void StaticObject::Collision(float fDeltaTime)
{
	Object::Collision(fDeltaTime);
}

void StaticObject::Render(HDC hDC, float fDeltaTime)
{
	Object::Render(hDC, fDeltaTime);
}


void StaticObject::Save(FILE * pFile)
{
	Object::Save(pFile);
}


void StaticObject::Load(FILE * pFile)
{
	Object::Load(pFile);
}


#pragma once

#include <Windows.h>
#include <vector>	
#include <list>
#include <unordered_map>
#include <memory>
#include <crtdbg.h> 
#include <typeinfo>
#include <functional>
#include <conio.h>

#include "Sound/fmod.h"
#include "Sound/fmod.hpp"

#include "Macro.h"
#include "Type.h"
#include "resource.h"
#include "Flag.h"


#pragma comment(lib, "msimg32")
#pragma comment(lib, "fmod_vc")



#define		PI		3.141592f
#define		GRAVITY		9.8f

//Path Key
#define ROOT_PATH		"RootPath"
#define	TEXTURE_PATH	"TexturePath"
#define	DATA_PATH		"DataPath"
#define SOUND_PATH		"SoundPath"

using namespace std;

template<typename T>
void Safe_Delete_VectorList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++)
	{
		SAFE_DELETE(*iter);
	}
	
	p.clear();
}

template<typename T>
void Safe_Release_VectorList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++)
	{
		SAFE_RELEASE(*iter);
	}

	p.clear();
	
}


template<typename T>
void Safe_Delete_map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();

}


template<typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++)
	{
		SAFE_RELEASE(iter->second);
	}

	p.clear();

}

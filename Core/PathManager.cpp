#include "PathManager.h"

PathManager* PathManager::m_pInst = nullptr;

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}


PathManager * PathManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new PathManager;
	}

	return m_pInst;
}

void PathManager::DestroyInst()
{
	delete m_pInst;
	m_pInst = nullptr;
}

bool PathManager::Init()
{
	wchar_t strPath[MAX_PATH] = {};
	

	GetModuleFileName(NULL, strPath, MAX_PATH);
	
	for (int i = lstrlen(strPath) - 1; i >= 0; i--)
	{
		if (strPath[i] == '/' || strPath[i] == '\\')
		{
			memset(strPath + (i + 1), 0, sizeof(wchar_t) * ((MAX_PATH)-(i + 1)));
			break;
		}
	}

	
	m_mapPath.insert(make_pair(ROOT_PATH, strPath));

	//Texture ��� ����
	if(! CreatePath(TEXTURE_PATH, L"Textures\\") )
	{
		return false;
	}


	//Data ��� ���� 
	if (!CreatePath(DATA_PATH, L"Data\\"))
	{
		return false;
	}
	
	//Data ��� ���� 
	if (!CreatePath(SOUND_PATH, L"Sound\\"))
	{
		return false;
	}

	return true;
}

bool PathManager::CreatePath(const string & strKey, const wchar_t * pPath, const string & strBaseKey)
{
	const wchar_t* pBasePath = FindPath(strBaseKey);

	wstring strPath;

	if (pBasePath)
	{
		strPath = pBasePath;
	}

	strPath += pPath;

	m_mapPath.insert(make_pair(strKey, strPath));

	return true;
}

const wchar_t * PathManager::FindPath(const string & strKey)
{
	unordered_map<string, wstring>::iterator iter = m_mapPath.find(strKey);

	if (iter == m_mapPath.end())
	{
		return nullptr;
	}

	return iter->second.c_str();
}


const char * PathManager::FindPathMultiByte(const string & strKey)
{
	const wchar_t* pPath = FindPath(strKey);

	if (!pPath) return nullptr;
	
	memset(m_strPath, 0, sizeof(char) * MAX_PATH);

	WideCharToMultiByte(CP_ACP, 0, pPath, -1, m_strPath, lstrlen(pPath) * 2, 0, 0);

	return m_strPath;
}

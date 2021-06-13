#pragma once
#include "Scene.h"

class MapEditScene :
	public Scene
{
private:
	friend class SceneManager;


private:
	MapEditScene();
	~MapEditScene();

	virtual bool Init();
	virtual void Input(float fDeltaTime);


private:
	TILE_EDIT_MODE	m_eTEM;
	TILE_OPTION		m_eEditOption;

	vector<class Texture*> m_vecTexture;
	int				m_iEditTileTex;
	class Stage*	m_pStage;
	
	static wchar_t	m_strText[MAX_PATH];

public:
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};


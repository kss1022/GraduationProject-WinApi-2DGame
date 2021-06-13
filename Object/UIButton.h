#pragma once
#include "UI.h"


enum BUTTON_STATE
{
	BS_NONE,
	BS_MOUSEON,
	BS_CLICK
};

class UIButton : 
	public UI
{
private:
	friend class Object;
	friend class Scene;

private:
	UIButton();
	UIButton(const UIButton& ui);
	~UIButton();

private:
	function<void(float fTime)> m_BtnCallBack;
	bool		m_bEnableCallback;
	BUTTON_STATE m_eState;
public:
	template<typename T>
	void SetCallback(T* pObj, void(T::*pFunc)(float));
	
	void SetCallback(void(pFunc)(float));
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int	 Update(float fDeltaTime);
	virtual int	 LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual	UIButton*	 Clone();


public:
	void MouseOn(Collider * pSrc, Collider * pDest, float fDeltaTime);
	void MouseOut(Collider * pSrc, Collider * pDest, float fDeltaTime);

};

template<typename T>
 void UIButton::SetCallback(T * pObj, void(T::* pFunc)(float))
{
	m_BtnCallBack = bind(pFunc, pObj,placeholders::_1);
	m_bEnableCallback = true;
}


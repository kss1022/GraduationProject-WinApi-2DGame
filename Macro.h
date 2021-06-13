#pragma once

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr;}
#define SAFE_RELEASE(p)if(p) { p->Release(); p = nullptr;}


#define DECLEAR_SINGLE(Type)	\
	privte:\
		static Type* m_pInst;\
	public:\
		static Type* GetInst()\
		{\
			if(!m_pInst) m_pInst = new Type;\
			return m_pInst;\
		}\
		static void DestroyInst()\
		{\
			SAFE_DELETE(m_pInst);\
		}\
	private:\
		Type();\
		~Type();

#define DEFINITION_SIGLE(Type) Type* Type::m_pInst = nullptr;
#define GET_SINGLE(Type)	 Type::GetInst()
#define DESTROY_SINGLE(Type)	Type::DestroyInst()
#define GETRESOLUTION	Core::GetInst()->GetResoulution()
#define WINDOWHANDLE	Core::GetInst()->GetWindowHandle()
#define WINDOWINSTANCE	Core::GetInst()->GetWindowInsatnce()

#define KEYDOWN(key)	Input::GetInst()->KeyDown(key)
#define KEYPRESS(key)	Input::GetInst()->KeyPress(key)
#define KEYUP(key)		Input::GetInst()->KeyUp(key)
#define KEYKEY(key)		KEYDOWN(key)	||	KEYPRESS(key)


#define MOUSECLINETPOS	Input::GetInst()->GetMouseClientPos()
#define MOUSEWORLDPOS	Input::GetInst()->GetMouseWorldPos()
#define MOUSEMOVE		Input::GetInst()->GetMouseMove()
#define	MOUSE			Input::GetInst()

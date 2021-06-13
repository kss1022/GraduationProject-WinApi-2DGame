#include "UI.h"
#include "../Animation/Animation.h"
#include "../Resource/Texture.h"


UI::UI()
{
}



UI::UI(const UI & ui) : Object(ui)
{
}

UI::~UI()
{
}

bool UI::Init()
{
	return true;
}

void UI::Input(float fDeltaTime)
{
	Object::Input(fDeltaTime);
}

int UI::Update(float fDeltaTime)
{
	Object::Update(fDeltaTime);

	return 0;
}

int UI::LateUpdate(float fDeltaTime)
{
	Object::LateUpdate(fDeltaTime);

	return 0;
}

void UI::Collision(float fDeltaTime)
{
	Object::Collision(fDeltaTime);

}

void UI::Render(HDC hDC, float fDeltaTime)
{

	if (m_pTexture)
	{
	
		POSITION tImagePos;

		if (m_pAnimation)
		{
			ANIMATIONCLIP* pClip = m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS)
			{
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y), static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y),
				m_pTexture->GetDC(), tImagePos.x, tImagePos.y, static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y), m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, static_cast<int>(m_tPos.x), static_cast<int>(m_tPos.y), static_cast<int>(m_tSize.x), static_cast<int>(m_tSize.y),
				m_pTexture->GetDC(), tImagePos.x, tImagePos.y, SRCCOPY);
		}
	}

	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);


		if (!(*iter)->GetLife())
		{
			(*iter)->Release();
			*iter = nullptr;

			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else iter++;
	}

	//Object::Render(hDC,fDeltaTime);

}

UI * UI::Clone()
{
	return nullptr;
}

#include "StageMap1.h"
#include "../Core.h"
#include "../Resource/Texture.h"
#include "../Core/Camera.h"
#include "../Object/Tile.h"
#include "../Scene/Layer.h"

#include "../Core/PathManager.h"
StageMap1::StageMap1()
{
}

StageMap1::StageMap1(const StageMap1 & stage) : StaticObject(stage)
{

}

StageMap1::~StageMap1()
{
}





bool StageMap1::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1861.f, 720.f);
	SetPivot(0.0f, 0.0f);

	SetTexture("Stage1", L"Stage/Stage.bmp");
	return true;
}



void StageMap1::Input(float fDeltaTime)
{
	StaticObject::Input(fDeltaTime);
}

int StageMap1::Update(float fDeltaTime)
{
	StaticObject::Update(fDeltaTime);


	return 0;
}

int StageMap1::LateUpdate(float fDeltaTime)
{
	StaticObject::LateUpdate(fDeltaTime);
	return 0;
}

void StageMap1::Collision(float fDeltaTime)
{
	StaticObject::Collision(fDeltaTime);
}

void StageMap1::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture)
	{
		POSITION	tPos = m_tPos - m_tSize * m_tPivot;

		POSITION	tCamPos = Camera::GetInst()->GetPos();


		BitBlt(hDC, tPos.x, tPos.y, Core::GetInst()->GetResoulution().iW, Core::GetInst()->GetResoulution().iH, m_pTexture->GetDC(), tCamPos.x, tCamPos.y, SRCCOPY);
	}
}

StageMap1 * StageMap1::Clone()
{
	return new StageMap1(*this);
}



void StageMap1::Save(FILE * pFile)
{
	StaticObject::Save(pFile);
}


void StageMap1::Load(FILE * pFile)
{
	StaticObject::Load(pFile);
}

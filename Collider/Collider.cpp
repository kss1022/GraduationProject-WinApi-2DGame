#include "Collider.h"
#include "../Math.h"

Collider::Collider()
{
}

Collider::Collider(const Collider & coll)
{
	*this = coll;
}

Collider::~Collider()
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderLIst.end();

	for (iter = m_ColliderLIst.begin(); iter != iterEnd; iter++)
	{
		(*iter)->EraseCollisionList(this);
	}
}


void Collider::AddCollider(Collider* pCollider)
{
	m_ColliderLIst.push_back(pCollider);
}

bool Collider::CheckCollisionList(Collider * pCollider)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderLIst.end();

	for (iter = m_ColliderLIst.begin(); iter != iterEnd; iter++)
	{
		if (*iter == pCollider)
		{
			return true;
		}
	}

	return false;
}

void Collider::EraseCollisionList(Collider * pCollider)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderLIst.end();

	for (iter = m_ColliderLIst.begin(); iter != iterEnd; iter++)
	{
		if (*iter == pCollider)
		{
			m_ColliderLIst.erase(iter);
			break;
		}
	}
}

void Collider::AddCollisionFunction(COLLISION_STATE eState, void(*pFunc)(Collider *, Collider *, float))
{
	function<void(Collider*, Collider*, float)> func;

	func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

	m_FuncList[eState].push_back(func);
}





bool Collider::Init()
{
	return true;
}

void Collider::Input(float fDeltaTime)
{
}

int Collider::Update(float fDeltaTime)
{
	return 0;
}

int Collider::LateUpdate(float fDeltaTime)
{

	return 0;
}

bool Collider::Collision(Collider * pDest)
{
	return false;
}


void Collider::Render(HDC hDC, float fDeltaTime)
{
}

Collider * Collider::Clone()
{
	return nullptr;
}

void Collider::Save(FILE * pFile)
{
	//Tag정보 저장
	int iLength = m_strTag.length();

	//Tag길이 저장
	fwrite(&iLength, 4, 1, pFile);

	//Tag 문자열 저장
	fwrite(m_strTag.c_str(), 1, iLength, pFile);

	//충돌체 타입저장
	fwrite(&m_eCollType, 4, 1, pFile);
}

void Collider::Load(FILE * pFile)
{
}

void Collider::Callfunction(COLLISION_STATE eState, Collider * pDest, float fDeltaTime)
{
	list<function < void(Collider*, Collider*, float)> > ::iterator iter;
	list<function < void(Collider*, Collider*, float)> > ::iterator iterEnd = m_FuncList[eState].end();

	for (iter = m_FuncList[eState].begin(); iter != iterEnd; iter++)
	{
		(*iter)(this, pDest, fDeltaTime);
	}
}

bool Collider::CollisionReactToReact(const RECTANGLE & src, const RECTANGLE & dest)
{
	if (src.l > dest.r)
	{
		return false;
	}
	else if (src.r < dest.l)
	{
		return false;
	}
	else if (src.t > dest.b)
	{
		return false;
	}
	else if (src.b < dest.t)
	{
		return false;
	}

	return true;
}

bool Collider::CollisionSphereToSphere(const SPHERE & src, const SPHERE & dest)
{
	float fDist = Math::Distance(src.tCenter, dest.tCenter);


	return fDist <= src.fRadius + dest.fRadius;
}



bool Collider::CollisionReactToSphere(const RECTANGLE & src, const SPHERE & dest)
{
	//원의 중점의 x좌표, y좌표가 사각형 영역에 있는지 체크
	if ((src.l <= dest.tCenter.x && dest.tCenter.x <= src.r) ||
		(src.t <= dest.tCenter.y && dest.tCenter.y <= src.b))
	{
		RECTANGLE	tRC = src;
		tRC.l -= dest.fRadius;
		tRC.t -= dest.fRadius;
		tRC.r += dest.fRadius;
		tRC.b += dest.fRadius;

		if (dest.tCenter.x < tRC.l)
		{
			return false;
		}
		else if (dest.tCenter.x > tRC.r)
		{
			return false;
		}
		else if (dest.tCenter.y < tRC.t)
		{
			return false;
		}
		else if (dest.tCenter.y > tRC.b)
		{
			return false;
		}

		return true;
	}

	POSITION tPos[4];
	tPos[0] = POSITION(src.l, src.t);
	tPos[1] = POSITION(src.r, src.t);
	tPos[2] = POSITION(src.l, src.b);
	tPos[3] = POSITION(src.r, src.b);


	for (int i = 0; i < 4; i++)
	{
		if (Math::Distance(tPos[i], dest.tCenter) <= dest.fRadius)
		{
			return true;
		}
	}

	return false;
}

bool Collider::CollisionReactToPixel(const RECTANGLE & src,
	const vector<PIXEL>& vecPixel, int iWidth, int iHeight)
{


	m_tHitPoint.x = -1;
	m_tHitPoint.y = -1;

	int iStartX, iEndX;
	int iStartY, iEndY;

	iStartX = (src.l < 0) ? 0 : src.l;
	iEndX = (src.r >= iWidth) ? iWidth - 1 : src.r;

	iStartY = (src.t < 0) ? 0 : src.t;
	iEndY = (src.b >= iWidth) ? iHeight - 1 : src.b;


	for (int i = iStartY; i <= iEndY; i += 5)
	{
		for (int j = iStartX; j <= iEndX; j += 5)
		{
			int index = i * iWidth + j;
//			if (index >= 1339920 || index < 0) return false;
			const PIXEL&	pixel = vecPixel[index];

			if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
			{
				m_tHitPoint.x = j;
				m_tHitPoint.y = i;
				return true;
			}

		}
	}

	return false;
}

bool Collider::CollisionSphereToPixel(const SPHERE & src, const vector<PIXEL>& vecPixel, int iWidth, int iHeight)
{
	return false;
}



bool Collider::CollisionReactToPoint(const RECTANGLE & src, const POSITION & dest)
{
	if (dest.x < src.l)
	{
		return false;
	}
	else if (dest.x > src.r)
	{
		return false;
	}
	else if (dest.y < src.t)
	{
		return false;
	}
	else if (dest.y > src.b)
	{
		return false;
	}
	return true;
}

bool Collider::CollisionSphereToPoint(const SPHERE & src, const POSITION & dest)
{
	return 	Math::Distance(src.tCenter, dest) <= src.fRadius;
}

bool Collider::CollisionPixelToPoint(const vector<PIXEL>& vecPixel, int iWidth, int iHeight, const POSITION & dest)
{
	if (dest.x < 0 || dest.y < 0 || dest.x >= iWidth || dest.y >= iHeight)
	{
		return false;
	}
	int index = static_cast<int>(dest.y) * iWidth + static_cast<int>(dest.x);

	const PIXEL&	pixel = vecPixel[index];

	if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
	{
		m_tHitPoint = dest;

		return true;
	}

	return false;
}

#pragma once
#include "Flag.h"

typedef struct _tagResolution
{
	unsigned int iH;
	unsigned int iW;

	_tagResolution() : iW(0), iH(0)
	{
	}

	_tagResolution(int x ,int y) : iW(x), iH(y)
	{
	}


}RESOLUTION;

typedef struct _tagPosition
{
	float x, y;


	_tagPosition() : x(0), y(0)
	{
	}

	_tagPosition(float _x, float _y) : x(_x), y(_y)
	{
	}

	_tagPosition(const _tagPosition& pos) : x(pos.x), y(pos.y)
	{
	}
	
	_tagPosition(const POINT& pt) : x(static_cast<float>(pt.x)), y(static_cast<float>(pt.y))
	{
	}




	////////////////////////////////
	void operator=(const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator=(const POINT& pt)
	{
		x = static_cast<float>(pt.x);
		y = static_cast<float>(pt.y);
	}


	void operator+=(const _tagPosition& pos)
	{
		x += pos.x;
		y += pos.y;
	}


	////////////////////////////////
	_tagPosition operator+(const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;

		return tPos;
	}


	_tagPosition operator+(const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x + static_cast<float>(pt.x);
		tPos.y = y + static_cast<float>(pt.y);

		return tPos;
	}



	

	////////////////////////////////
	_tagPosition operator-(const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;

		return tPos;
	}


	_tagPosition operator-(const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x - static_cast<float>(pt.x);
		tPos.y = y - static_cast<float>(pt.y);

		return tPos;
	}

	void operator-=(const _tagPosition& pos)
	{
		x -= pos.x;
		y -= pos.y;
	}

	////////////////////////////////
	_tagPosition operator*(const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;

		return tPos;
	}



	_tagPosition operator*(const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x * static_cast<float>(pt.x);
		tPos.y = y * static_cast<float>(pt.y);

		return tPos;
	}

	_tagPosition operator*(float f) const
	{
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;

		return tPos;
	}


	////////////////////////////////
	_tagPosition operator/(const _tagPosition& pos) const
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;

		return tPos;
	}


	_tagPosition operator/(const POINT& pt) const
	{
		_tagPosition tPos;
		tPos.x = x / static_cast<float>(pt.x);
		tPos.y = y / static_cast<float>(pt.y);

		return tPos;
	}

}POSITION, _SIZE;

typedef struct _tagRectangle
{
	float l;
	float t;
	float r;
	float b;

	_tagRectangle() : l(0.f) , t(0.f), r(0.f), b(0.f)
	{

	}
}RECTANGLE;


typedef struct _tagSphere
{
	POSITION tCenter;
	float	 fRadius;

	_tagSphere() : tCenter(0.f, 0.f), fRadius(0.f)
	{
	}
}SPHERE;


typedef struct _tagPixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

}PIXEL;

typedef struct _tagAnimationClip
{
	ANIMATION_TYPE		eType;
	ANIMATION_OPTION	eOption;
	std::vector<class Texture*> vecTexture;

	float	fAnimationTime;
	float	fAnimationLimitTime;
	float	fAnimationFrameTime;

	int iFrameX;
	int iFrameY;
	int iFrameMaxX;
	int iFrameMaxY;
	int iStartX;
	int iStartY;
	int iLengthX;
	int iLengthY;

	float fOptionTime;
	float fOptionLimitTime;

	_SIZE tFrameSize;
}ANIMATIONCLIP;
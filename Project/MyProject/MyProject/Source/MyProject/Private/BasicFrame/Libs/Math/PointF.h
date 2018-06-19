#ifndef __PointF_H
#define __PointF_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PointF
{
protected:
	float mX;
    float mY;

public:
	PointF(float x, float y);
	float getX();
	void setX(float value);
	float getY();
	void setY(float value);
};

MY_END_NAMESPACE

#endif
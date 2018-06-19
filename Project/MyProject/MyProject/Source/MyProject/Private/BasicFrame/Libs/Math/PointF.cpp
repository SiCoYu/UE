#include "MyProject.h"
#include "PointF.h"

MY_BEGIN_NAMESPACE(MyNS)

PointF::PointF(float x, float y)
{
	mX = x;
	mY = y;
}

float PointF::getX()
{
	return mX;
}
void PointF::setX(float value)
{
	mX = value;
}

float PointF::getY()
{
	return mY;
}

void PointF::setY(float value)
{
	mY = value;
}

MY_END_NAMESPACE
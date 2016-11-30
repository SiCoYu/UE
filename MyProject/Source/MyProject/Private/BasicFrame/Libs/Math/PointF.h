#ifndef __PointF_H
#define __PointF_H

class PointF
{
protected:
	float m_x;
    float m_y;

public:
	PointF(float x, float y);
	float getX();
	void setX(float value);
	float getY();
	void setY(float value);
};

#endif
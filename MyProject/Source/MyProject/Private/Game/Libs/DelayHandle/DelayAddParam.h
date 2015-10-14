#ifndef __DelayAddParam_H
#define __DelayAddParam_H

#include "DelayHandleParamBase.h"

class DelayAddParam : public DelayHandleParamBase
{
public:
	float m_priority;

public:
	DelayAddParam();
};

#endif
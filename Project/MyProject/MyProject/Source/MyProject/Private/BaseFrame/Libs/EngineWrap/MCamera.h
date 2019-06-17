#ifndef __MCamera_H
#define __MCamera_H

#include "PlatformDefine.h"

class APlayerCameraManager;

MY_BEGIN_NAMESPACE(MyNS)

class MCamera
{
protected:
	APlayerCameraManager* m_pAPlayerCameraManager;

public:
	float GetFOVAngle();
};

MY_END_NAMESPACE

#endif
#ifndef __MCamera_H
#define __MCamera_H

class APlayerCameraManager;

class MCamera
{
protected:
	APlayerCameraManager* m_pAPlayerCameraManager;

public:
	float GetFOVAngle();
};

#endif
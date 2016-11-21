#ifndef __ENGINEDATA_H
#define __ENGINEDATA_H

#include "MyProject.h"

class EngineData
{
protected:
	//UObject* m_mainActor;
	AActor* m_mainActor;

public:
	//UObject* getMainActor();
	//void setMainActor(UObject* actor);
	AActor* getMainActor();
	void setMainActor(AActor* actor);
};

#endif				// __ENGINEDATA_H
#ifndef __ENGINEDATA_H
#define __ENGINEDATA_H

#include "MyProject.h"

class EngineData
{
protected:
	UObject* m_mainActor;

public:
	UObject* getMainActor();
	void setMainActor(UObject* actor);
};

#endif				// __ENGINEDATA_H
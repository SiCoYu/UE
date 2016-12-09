#ifndef __ENGINEDATA_H
#define __ENGINEDATA_H

#include "MyProject.h"

class EngineData
{
protected:
	//UObject* m_mainActor;
	AActor* m_mainActor;
	APlayerController* mMainPlayerController;

public:
	//UObject* getMainActor();
	//void setMainActor(UObject* actor);
	AActor* getMainActor();
	void setMainActor(AActor* actor);

	APlayerController* getMainPlayerController();
	void setMainPlayerController(APlayerController* playerController);
};

#endif				// __ENGINEDATA_H
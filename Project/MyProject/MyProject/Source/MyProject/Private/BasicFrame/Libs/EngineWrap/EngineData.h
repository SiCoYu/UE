#ifndef __EngineData_H
#define __EngineData_H

#include "GObject.h"
#include "PlatformDefine.h"

class AActor;
class APlayerController;
class UMyGameEngineBase;

MY_USING_NAMESPACE(MyNS)

class EngineData : public GObject
{
protected:
	AActor* mMainActor;
	APlayerController* mMainPlayerController;
	UMyGameEngineBase* mMyEngine;

public:
	EngineData();
	~EngineData();

public:
	void init();
	void dispose();

	AActor* getMainActor();
	void setMainActor(AActor* actor);

	APlayerController* getMainPlayerController();
	void setMainPlayerController(APlayerController* playerController);

	UMyGameEngineBase* getMyEngine();
	void setMyEngine(UMyGameEngineBase* myEngine);
};

#endif				// __ENGINEDATA_H
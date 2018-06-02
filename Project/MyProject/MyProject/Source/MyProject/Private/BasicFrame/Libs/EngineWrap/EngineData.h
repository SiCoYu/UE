#ifndef __EngineData_H
#define __EngineData_H

#include "GObject.h"
#include "PlatformDefine.h"

class AActor;
class APlayerController;
class UMyGameEngineBase;

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE

#endif				// __EngineData_H
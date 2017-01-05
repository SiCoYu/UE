#ifndef __EngineData_H
#define __EngineData_H

class AActor;
class APlayerController;
class UMyEngine;

class EngineData
{
protected:
	AActor* mMainActor;
	APlayerController* mMainPlayerController;
	UMyEngine* mMyEngine;

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

	UMyEngine* getMyEngine();
	void setMyEngine(UMyEngine* myEngine);
};

#endif				// __ENGINEDATA_H
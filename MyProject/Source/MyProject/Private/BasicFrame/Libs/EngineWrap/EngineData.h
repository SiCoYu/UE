#ifndef __EngineData_H
#define __EngineData_H

class AActor;
class APlayerController;
class UMyEngine;

class EngineData
{
protected:
	//UObject* m_mainActor;
	AActor* m_mainActor;
	APlayerController* mMainPlayerController;
	UMyEngine* mMyEngine;

public:
	//UObject* getMainActor();
	//void setMainActor(UObject* actor);
	AActor* getMainActor();
	void setMainActor(AActor* actor);

	APlayerController* getMainPlayerController();
	void setMainPlayerController(APlayerController* playerController);

	UMyEngine* getMyEngine();
	void setMyEngine(UMyEngine* myEngine);
};

#endif				// __ENGINEDATA_H
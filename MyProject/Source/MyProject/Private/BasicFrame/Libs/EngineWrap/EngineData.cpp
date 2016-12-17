#include "MyProject.h"
#include "EngineData.h"

void EngineData::setMainActor(AActor* actor)
{
	mMainActor = actor;
}

AActor* EngineData::getMainActor()
{
	return mMainActor;
}

APlayerController* EngineData::getMainPlayerController()
{
	return this->mMainPlayerController;
}

void EngineData::setMainPlayerController(APlayerController* playerController)
{
	this->mMainPlayerController = playerController;
}

UMyEngine* EngineData::getMyEngine()
{
	return mMyEngine;
}

void EngineData::setMyEngine(UMyEngine* myEngine)
{
	mMyEngine = myEngine;
}
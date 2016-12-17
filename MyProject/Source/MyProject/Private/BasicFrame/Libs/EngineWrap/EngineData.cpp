#include "MyProject.h"
#include "EngineData.h"

void EngineData::setMainActor(AActor* actor)
{
	m_mainActor = actor;
}

AActor* EngineData::getMainActor()
{
	return m_mainActor;
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
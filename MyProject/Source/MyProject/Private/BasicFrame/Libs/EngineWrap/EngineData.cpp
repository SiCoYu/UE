#include "MyProject.h"
#include "EngineData.h"

EngineData::EngineData()
{

}

EngineData::~EngineData()
{

}

void EngineData::init()
{

}

void EngineData::dispose()
{

}

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

UMyGameEngineBase* EngineData::getMyEngine()
{
	return mMyEngine;
}

void EngineData::setMyEngine(UMyGameEngineBase* myEngine)
{
	mMyEngine = myEngine;
}
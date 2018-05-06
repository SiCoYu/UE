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
	this->mMainActor = actor;
}

AActor* EngineData::getMainActor()
{
	return this->mMainActor;
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
	return this->mMyEngine;
}

void EngineData::setMyEngine(UMyGameEngineBase* myEngine)
{
	this->mMyEngine = myEngine;
}
#include "MyProject.h"
#include "EngineApi.h"

UGameInstance* EngineApi::getGameInstance()
{
	return UGameplayStatics::GetGameInstance(Ctx::getSingletonPtr()->getEngineData()->getMainActor());
}
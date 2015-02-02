#include "MyProject.h"
#include "EngineApi.h"
#include "Ctx.h"
#include "EngineData.h"

UGameInstance* EngineApi::getGameInstance()
{
	return UGameplayStatics::GetGameInstance(Ctx::getSingletonPtr()->getEngineData()->getMainActor());
}
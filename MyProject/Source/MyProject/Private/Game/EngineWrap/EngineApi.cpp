#include "MyProject.h"
#include "EngineApi.h"
#include "Ctx.h"
#include "EngineData.h"

UGameInstance* EngineApi::getGameInstance()
{
	return UGameplayStatics::GetGameInstance(Ctx::getSingletonPtr()->getEngineData()->getMainActor());
}

UWorld* EngineApi::getWorld()
{
	UWorld* World = GEngine->GetWorldFromContextObject(Ctx::getSingletonPtr()->getEngineData()->getMainActor());
	return World;
}

void EngineApi::showCursor()
{
	UWorld* World = getWorld();
	if (World)
	{
		World->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	FSlateApplication::Get().GetPlatformApplication()->Cursor->Show(true);
}

void EngineApi::addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName)
{
	TScriptDelegate<FWeakObjectPtr> ptrDelegate;
	ptrDelegate.BindUFunction(pFuncObj, funcName);
	pBtn->OnClicked.Add(ptrDelegate);
}
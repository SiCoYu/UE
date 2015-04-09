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

UMyProjectEngine* EngineApi::getEngine()
{
	UEngine* const Engine = GetEngine();
	return Cast<UMyProjectEngine>(Engine);
}

UMyProjectGameInstance* EngineApi::getMyProjectGameInstanceByEngine()
{
	UEngine* const Engine = GetEngine();
	UMyProjectGameInstance* pUMyProjectGameInstance = Cast<UMyProjectEngine>(Engine);
	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(pUMyProjectGameInstance->GameInstance);
	return GI;
}

UWorld* EngineApi::getWorldByEngine()
{
	UMyProjectGameInstance* pUMyProjectGameInstance = getMyProjectGameInstanceByEngine();
	UWorld* const World = pUMyProjectGameInstance->GetWorld();
	return World;
}
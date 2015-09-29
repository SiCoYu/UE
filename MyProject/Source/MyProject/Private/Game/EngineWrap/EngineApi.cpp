#include "MyProject.h"
#include "EngineApi.h"
#include "Ctx.h"
#include "EngineData.h"
#include "MyProjectEngine.h"
#include "MyProjectGameInstance.h"

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
	return Cast<UMyProjectEngine>(GEngine);
}

UMyProjectGameInstance* EngineApi::getMyProjectGameInstanceByEngine()
{
	UMyProjectEngine* pUMyProjectEngine = Cast<UMyProjectEngine>(GEngine);
	UMyProjectGameInstance* const GI = Cast<UMyProjectGameInstance>(pUMyProjectEngine->GameInstance);
	return GI;
}

UWorld* EngineApi::getWorldByEngine()
{
	UMyProjectGameInstance* pUMyProjectGameInstance = getMyProjectGameInstanceByEngine();
	UWorld* const World = pUMyProjectGameInstance->GetWorld();
	return World;
}

ACharacter* EngineApi::getFirstCharacter()
{
	ACharacter* Character = nullptr;
	APlayerController* PC = nullptr;
	UWorld* World = getWorld();
	if (World)
	{
		PC = World->GetFirstPlayerController();
		if (PC != nullptr)
		{
			Character = Cast<ACharacter>(PC->GetPawn());
		}
	}

	return Character;
}
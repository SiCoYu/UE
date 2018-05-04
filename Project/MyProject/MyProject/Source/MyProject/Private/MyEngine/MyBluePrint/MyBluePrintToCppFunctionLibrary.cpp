#include "MyProject.h"
#include "MyBluePrintToCppFunctionLibrary.h"
#include "MyBluePrintBase.h"
#include "Ctx.h"
#include "EngineApi.h"
#include "EngineData.h"
#include "UMGWidget.h"				// UUMGWidget

UMyBluePrintToCppFunctionLibrary::UMyBluePrintToCppFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UMyBluePrintBase* UMyBluePrintToCppFunctionLibrary::getBPCtx()
{
	return GBPCtx.get();
}

ACharacter* UMyBluePrintToCppFunctionLibrary::getFirstCharacter()
{
	return EngineApi::getFirstCharacter();
}

AMyPlayerControllerBase* UMyBluePrintToCppFunctionLibrary::GetPlayerController()
{
	return EngineApi::GetPlayerController();
}

UUMGWidget* UMyBluePrintToCppFunctionLibrary::createWidget(UClass* WidgetClass)
{
	UUMGWidget* WidgetObject = nullptr;

	WidgetObject = EngineApi::CreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), WidgetClass);

	return WidgetObject;
}

UObject* UMyBluePrintToCppFunctionLibrary::newObjectFromBlueprint(UClass* cls)
{
	APlayerController* playerController = (APlayerController*)EngineApi::GetPlayerController();
	UObject* tempObject = NewObject<UObject>(playerController, cls);

	return tempObject;
}
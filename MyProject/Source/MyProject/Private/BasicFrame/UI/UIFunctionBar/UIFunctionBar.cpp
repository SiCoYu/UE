#include "MyProject.h"
#include "UIFunctionBar.h"
#include "UtilApi.h"
#include "FunctionBarCV.h"
#include "EngineApi.h"
#include "Common.h"
#include "Engine/LatentActionManager.h"

UUIFunctionBar::UUIFunctionBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUIFunctionBar::onReady()
{
	Super::onReady();

	UtilApi::addUObjectButtonClickHandle(mGuiWin->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
}

void UUIFunctionBar::onTestButtonTouch()
{
	FLatentActionInfo info;
	info.ExecutionFunction = "onLevelLoaded";
	info.CallbackTarget = this;

	EngineApi::LoadStreamLevel(GEngineData->getMainActor(), "TestMap2", true, true, info);
}

void UUIFunctionBar::onLevelLoaded()
{
	int num = 0;
}
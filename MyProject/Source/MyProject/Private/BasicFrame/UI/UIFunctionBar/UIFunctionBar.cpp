#include "MyProject.h"
#include "UIFunctionBar.h"
#include "UtilApi.h"
#include "FunctionBarCV.h"
#include "EngineApi.h"
#include "Common.h"

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
	EngineApi::LoadStreamLevel(GEngineData->getMainActor());
}
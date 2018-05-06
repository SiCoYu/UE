#include "MyProject.h"
#include "UiFunctionBar.h"
#include "UtilApi.h"
#include "FunctionBarCV.h"
#include "EngineApi.h"
#include "Common.h"
#include "Engine/LatentActionManager.h"
#include "IDispatchObject.h"
#include "EventDispatchDelegate.h"
#include "SafePointer.h"

UUiFunctionBar::UUiFunctionBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	mTestButton = MySharedPtr<AuxButton>(SAFE_NEW AuxButton());
}

void UUiFunctionBar::onReady()
{
	Super::onReady();

	//UtilApi::addUObjectButtonClickHandle(mWinRender->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
	mTestButton->addUObjectButtonClickHandle(mWinRender->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
}

void UUiFunctionBar::onTestButtonTouch()
{
	//FLatentActionInfo info;
	//info.ExecutionFunction = "onLevelLoaded";
	//info.CallbackTarget = this;
	//info.UUID = 0;
	//// Linkage 一定要有值，具体参考
	//// Engine\Source\Runtime\Engine\Private\LevelStreaming.cpp
	//// Response.FinishAndTriggerIf(bIsOperationFinished, LatentInfo.ExecutionFunction, LatentInfo.Linkage, LatentInfo.CallbackTarget);
	//// Engine\Source\Runtime\Engine\Private\LatentActionManager.cpp
	//// if (LinkInfo.LinkID != INDEX_NONE)
	//info.Linkage = 0;

	//EngineApi::LoadStreamLevel(GEngineData->getMainActor(), "/Game/MyAsset/Map/TestMap2", true, true, info);
	////EngineApi::SetClientTravel(EngineApi::GetWorld(), TEXT("/Game/MyAsset/Map/TestMap2"), TRAVEL_Absolute);
	////EngineApi::ServerTravel(TEXT("/Game/MyAsset/Map/TestMap2?game=TDM?listen"));

	GSceneSys->loadScene("/Game/MyAsset/Map/TestMap2", EventDispatchDelegate(this, &UUiFunctionBar::onLevelLoadedDispatch));
}

void UUiFunctionBar::onLevelLoaded()
{
	int num = 0;
}

void UUiFunctionBar::onLevelLoadedDispatch(IDispatchObject* dispObj)
{
	int num = 0;
}
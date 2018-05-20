#include "MyProject.h"
#include "UiFunctionBar.h"
#include "UtilSysLibWrap.h"
#include "FunctionBarCV.h"
#include "UtilEngineWrap.h"
#include "Prequisites.h"
#include "Engine/LatentActionManager.h"
#include "IDispatchObject.h"
#include "EventDispatchDelegate.h"
#include "SafePointer.h"	// SAFE_NEW
#include "MyFlyPawn.h"		// AMyFlyPawn
#include "UtilEngineWrap.h"

UUiFunctionBar::UUiFunctionBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->mTestButton = MySharedPtr<AuxButton>(SAFE_NEW AuxButton());
	this->mTestComBtn = SAFE_NEW AuxButton();
	this->mTestLoadTextureBtn = SAFE_NEW AuxButton();
	this->mTestLoadMaterialBtn = SAFE_NEW AuxButton();
	this->mTestChangeMaterialBtn = SAFE_NEW AuxButton();
}

void UUiFunctionBar::onReady()
{
	Super::onReady();

	//UtilSysLibWrap::addUObjectButtonClickHandle(mWinRender->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
	this->mTestButton->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
	this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestComBtn.c_str(), this, "onTestComBtnTouch");
	this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestLoadTextureBtn.c_str(), this, "onTestLoadTextureBtnTouch");
	this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestLoadMaterialBtn.c_str(), this, "onTestLoadMaterialBtnTouch");
	this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestChangeMaterialBtn.c_str(), this, "onTestChangeMaterialBtnTouch");
}

void UUiFunctionBar::onTestButtonTouch()
{
	//FLatentActionInfo info;
	//info.ExecutionFunction = "onLevelLoaded";
	//info.CallbackTarget = this;
	//info.UUID = 0;
	// Linkage 一定要有值，具体参考
	// Engine\Source\Runtime\Engine\Private\LevelStreaming.cpp
	// Response.FinishAndTriggerIf(bIsOperationFinished, LatentInfo.ExecutionFunction, LatentInfo.Linkage, LatentInfo.CallbackTarget);
	// Engine\Source\Runtime\Engine\Private\LatentActionManager.cpp
	// if (LinkInfo.LinkID != INDEX_NONE)
	//info.Linkage = 0;

	//UtilEngineWrap::LoadStreamLevel(GEngineData->getMainActor(), "/Game/MyAsset/Map/TestMap2", true, true, info);
	////UtilEngineWrap::SetClientTravel(UtilEngineWrap::GetWorld(), TEXT("/Game/MyAsset/Map/TestMap2"), TRAVEL_Absolute);
	////UtilEngineWrap::ServerTravel(TEXT("/Game/MyAsset/Map/TestMap2?game=TDM?listen"));

	GSceneSys->loadScene(
		"/Game/MyAsset/Map/TestMap2", 
		MakeEventDispatchDelegate(
			this, 
			&UUiFunctionBar::onLevelLoadedDispatch
		)
	);

	//FScriptGeneratorPlugin& scriptGeneratorPlugin = FModuleManager::GetModuleChecked<FScriptGeneratorPlugin>("ScriptGeneratorPlugin");

	//if (FScriptGeneratorPlugin.IsValid())
	//{
	//	scriptGeneratorPlugin.FinishExport();
	//}
}

void UUiFunctionBar::onTestComBtnTouch()
{
	APawn* actor = UtilEngineWrap::getFirstCharacter();
	UActorComponent* actorCom = UtilEngineWrap::getComponentByClass<UCameraComponent>(actor);
}

void UUiFunctionBar::onTestLoadTextureBtnTouch()
{
}

void UUiFunctionBar::onTestLoadMaterialBtnTouch()
{
}

void UUiFunctionBar::onTestChangeMaterialBtnTouch()
{

}

void UUiFunctionBar::onLevelLoaded()
{
	int num = 0;
}

void UUiFunctionBar::onLevelLoadedDispatch(IDispatchObject* dispObj)
{
	int num = 0;
}
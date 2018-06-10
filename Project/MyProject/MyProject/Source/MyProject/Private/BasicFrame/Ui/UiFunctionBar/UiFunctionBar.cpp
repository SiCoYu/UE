#include "MyProject.h"
#include "UiFunctionBar.h"
#include "UtilSysLibWrap.h"
#include "FunctionBarCV.h"
#include "UtilEngineWrap.h"
#include "Prequisites.h"
#include "Engine/LatentActionManager.h"
#include "IDispatchObject.h"
#include "EventDispatchDelegate.h"
#include "SafePointer.h"	// MY_SAFE_DISPOSE
#include "MyFlyPawn.h"		// AMyFlyPawn
#include "UtilEngineWrap.h"
#include "AuxTextureLoader.h"
#include "AuxMaterialLoader.h"

UUiFunctionBar::UUiFunctionBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UUiFunctionBar::onInit()
{
	Super::onInit();

	this->mTestButton = MySharedPtr<AuxButton>(MY_NEW AuxButton());
	this->mTestComBtn = MY_NEW AuxButton();
	this->mTestLoadTextureBtn = MY_NEW AuxButton();
	this->mTestLoadMaterialBtn = MY_NEW AuxButton();
	this->mTestChangeMaterialBtn = MY_NEW AuxButton();
}

void UUiFunctionBar::onReady()
{
	Super::onReady();

	//UtilSysLibWrap::addUObjectButtonClickHandle(mWinRender->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
	//this->mTestButton->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::ButtonTest.c_str(), this, "onTestButtonTouch");
	//this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestComBtn.c_str(), this, "onTestComBtnTouch");
	//this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestLoadTextureBtn.c_str(), this, "onTestLoadTextureBtnTouch");
	//this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestLoadMaterialBtn.c_str(), this, "onTestLoadMaterialBtnTouch");
	//this->mTestComBtn->addUObjectButtonClickHandle(this->mWinRender->mUiRoot, FunctionBarCV::TestChangeMaterialBtn.c_str(), this, "onTestChangeMaterialBtnTouch");
	this->mTestButton->addUObjectButtonClickHandle(
		this->mWinRender->mUiRoot, 
		FunctionBarCV_ButtonTest,
		this, 
		"onTestButtonTouch"
	);
	this->mTestComBtn->addUObjectButtonClickHandle(
		this->mWinRender->mUiRoot, 
		FunctionBarCV_TestComBtn,
		this, 
		"onTestComBtnTouch"
	);
	this->mTestLoadTextureBtn->addUObjectButtonClickHandle(
		this->mWinRender->mUiRoot, 
		FunctionBarCV_TestLoadTextureBtn,
		this, 
		"onTestLoadTextureBtnTouch"
	);
	this->mTestLoadMaterialBtn->addUObjectButtonClickHandle(
		this->mWinRender->mUiRoot, 
		FunctionBarCV_TestLoadMaterialBtn,
		this, 
		"onTestLoadMaterialBtnTouch"
	);
	this->mTestChangeMaterialBtn->addUObjectButtonClickHandle(
		this->mWinRender->mUiRoot, 
		FunctionBarCV_TestChangeMaterialBtn,
		this, 
		"onTestChangeMaterialBtnTouch"
	);
}

void UUiFunctionBar::onExit()
{
	this->mTestButton->dispose();
	this->mTestButton.setNull();
	
	MY_SAFE_DISPOSE(nullptr != this->mTestComBtn);
	MY_SAFE_DISPOSE(nullptr != this->mTestLoadTextureBtn);
	MY_SAFE_DISPOSE(nullptr != this->mTestLoadMaterialBtn);
	MY_SAFE_DISPOSE(nullptr != this->mTestChangeMaterialBtn);

	Super::onExit();
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
	AuxTextureLoader auxTextureLoader;
	auxTextureLoader.syncLoad("Texture2D'/Game/MyAsset/Textures/T_Fire_Tiled_D1.T_Fire_Tiled_D1'");
}

void UUiFunctionBar::onTestLoadMaterialBtnTouch()
{
	AuxMaterialLoader auxMaterialLoader;
	auxMaterialLoader.syncLoad("Material'/Game/MyAsset/Materials/TestMaterial.TestMaterial'");
	//auxMaterialLoader.syncLoad("MaterialInstanceConstant'/Game/MyAsset/Materials/TestMaterialInstanceConstant.TestMaterialInstanceConstant'");
}

void UUiFunctionBar::onTestChangeMaterialBtnTouch()
{
	AuxMaterialLoader auxMaterialLoader;
	auxMaterialLoader.syncLoad("Material'/Game/MyAsset/Materials/TestMaterial.TestMaterial'");

	APawn* actor = UtilEngineWrap::getFirstCharacter();
	UStaticMeshComponent* actorCom = UtilEngineWrap::getComponentByClass<UStaticMeshComponent>(actor);
	UtilEngineWrap::SetMaterial(actorCom, 0, auxMaterialLoader.getMaterialInterface());
}

void UUiFunctionBar::onLevelLoaded()
{
	int num = 0;
}

void UUiFunctionBar::onLevelLoadedDispatch(IDispatchObject* dispObj)
{
	int num = 0;
}
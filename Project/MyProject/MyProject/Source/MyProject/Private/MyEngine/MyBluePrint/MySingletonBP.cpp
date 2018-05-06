#include "MyProject.h"
#include "MySingletonBP.h"
#include "UtilEngineWrap.h"

UMySingletonBP* UMySingletonBP::msSingleton;

// 是否指针有效
bool UMySingletonBP::isValid()
{
	return (nullptr != UMySingletonBP::msSingleton);
}

UMySingletonBP* UMySingletonBP::getSingleton()
{
	if (!UMySingletonBP::isValid() || !IsValid(UMySingletonBP::msSingleton))
	{
		// 一定要添加 "_C"
		UClass *SingletonClass = LoadClass<UObject>(NULL, TEXT("/Game/MyAsset/MyBlueprints/Lib/FrameWork/Ctx.Ctx_C"), NULL, LOAD_None, NULL);
		// UMySingletonBP::msSingleton = (UMySingletonBP*)ConstructObject<UObject>(SingletonClass);
		// UMySingletonBP::msSingleton = Cast<UMySingletonBP>(StaticConstructObject(SingletonClass, nullptr));
		// UMySingletonBP::msSingleton = LoadObject<UMySingletonBP>(nullptr, TEXT("/Game/Table/ObjectBase_client"));
		// 第一个参数为 nullptr， 会报错， 位置
		// Engine\Source\Runtime\CoreUObject\Private\UObject\UObjectGlobals.cpp
		// UE_LOG(LogUObjectGlobals, Fatal, TEXT("%s"), *FString::Printf( TEXT("Object is not packaged: %s %s"), *InClass->GetName(), *InName.ToString()) );
		// UMySingletonBP::msSingleton = NewObject<UMySingletonBP>(nullptr, SingletonClass);
		UGameInstance* pGameIns = (UGameInstance*)UtilEngineWrap::GetGameInstance();
		UMySingletonBP::msSingleton = ::NewObject<UMySingletonBP>(pGameIns, SingletonClass, FName("UMySingletonBP"));
	}

	return UMySingletonBP::msSingleton;
}

UMySingletonBP::UMySingletonBP(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void UMySingletonBP::init()
{
	// https://answers.unrealengine.com/questions/116529/call-blueprint-functions-from-c.html?sort=oldest
	//FString cmd = FString::Printf(TEXT("Ctx init"));
	FString cmd = TEXT("init");
	FOutputDeviceDebug device;
	this->CallFunctionByNameWithArguments(*cmd, device, NULL, true);
}
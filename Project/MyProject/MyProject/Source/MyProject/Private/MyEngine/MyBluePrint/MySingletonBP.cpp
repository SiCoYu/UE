#include "MyProject.h"
#include "MySingletonBP.h"

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
		UClass *SingletonClass = LoadClass<UObject>(NULL, TEXT("/Game/MyAsset/MyBlueprints/Lib/FrameWork/Ctx.Ctx"), NULL, LOAD_None, NULL);
		//UMySingletonBP::msSingleton = (UMySingletonBP*)ConstructObject<UObject>(SingletonClass);
		//UMySingletonBP::msSingleton = Cast<UMySingletonBP>(StaticConstructObject(SingletonClass, nullptr));
		//UMySingletonBP::msSingleton = LoadObject<UMySingletonBP>(nullptr, TEXT("/Game/Table/ObjectBase_client"));
		UMySingletonBP::msSingleton = NewObject<UMySingletonBP>(nullptr, SingletonClass);
	}

	return UMySingletonBP::msSingleton;
}

UMySingletonBP::UMySingletonBP(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void UMySingletonBP::init()
{
	FString cmd = FString::Printf(TEXT("Ctx init"));
	FOutputDeviceDebug device;
	this->CallFunctionByNameWithArguments(*cmd, device, NULL, true);
}
#include "MyProject.h"
#include "MySingletonBP.h"

UMySingletonBP* UMySingletonBP::msSingleton;

// 是否是有效数据
bool UMySingletonBP::isValid()
{
	return (nullptr != UMySingletonBP::msSingleton);
}

UMySingletonBP* UMySingletonBP::getSingleton()
{
	if (!UMySingletonBP::isValid() || !IsValid(UMySingletonBP::msSingleton))
	{
		UClass *SingletonClass = LoadClass<UObject>(NULL, TEXT("/Game/MyAsset/MyBlueprints/Lib/FrameWork/Ctx.Ctx"), NULL, LOAD_None, NULL);
		UMySingletonBP::msSingleton = (UMySingletonBP*)ConstructObject<UObject>(SingletonClass);
	}

	return UMySingletonBP::msSingleton;
}
#include "MyProject.h"
#include "MyGameInstance.h"

#include "AppFrame.h"
//#include "Ctx.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	mAppFrame = new AppFrame();
}

void UMyGameInstance::Init()
{
	Super::Init();

	// UGameEngine 创建后，就创建 UGameInstance，这个是除 UGameEngine 外最早初始化的地方
	mAppFrame->initApp();
}
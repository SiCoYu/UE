#include "MyProject.h"
#include "MyGameInstance.h"

#include "AppFrame.h"
//#include "Ctx.h"
#include "UtilStr.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	mAppFrame = new AppFrame();

	// 这个设置等价于在 Project Setting 中的设置
	std::string aaa = "aaa";
	//GetDefault<UGeneralProjectSettings>()->ProjectDisplayedTitle = UtilStr::ConvStdStr2FText(aaa);
	//GetDefault<UInputSettings>()->DefaultViewportMouseCaptureMode = EMouseCaptureMode::CaptureDuringMouseDown;
}

void UMyGameInstance::Init()
{
	Super::Init();

	// UGameEngine 创建后，就创建 UGameInstance，这个是除 UGameEngine 外最早初始化的地方
	mAppFrame->initApp();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMyGameInstance::FinishDestroy()
{
	Super::FinishDestroy();
}
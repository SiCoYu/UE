#include "MyProject.h"
#include "MyGameInstance.h"

#include "AppFrame.h"
//#include "Ctx.h"
#include "UtilStr.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 逻辑指针不要放在构造函数中，因为脚本会调用一次构造函数，这样就会申请多个指针
	//mAppFrame = new AppFrame();

	// 这个设置等价于在 Project Setting 中的设置
	std::string aaa = "aaa";
	//GetDefault<UGeneralProjectSettings>()->ProjectDisplayedTitle = UtilStr::ConvStdStr2FText(aaa);
	//GetDefault<UInputSettings>()->DefaultViewportMouseCaptureMode = EMouseCaptureMode::CaptureDuringMouseDown;
}

void UMyGameInstance::Init()
{
	Super::Init();

	// UGameEngine 创建后，就创建 UGameInstance，这个是除 UGameEngine 外最早初始化的地方
	mAppFrame = new AppFrame();
	mAppFrame->initApp();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	mAppFrame->quitApp();
}

void UMyGameInstance::FinishDestroy()
{
	Super::FinishDestroy();
}
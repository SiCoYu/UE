#include "MyProject.h"
#include "MyGameInstanceBase.h"

#include "AppFrame.h"
//#include "Ctx.h"
#include "UtilStr.h"
#include "MyOnlineSession.h"

UMyGameInstanceBase::UMyGameInstanceBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 逻辑指针不要放在构造函数中，因为脚本会调用一次构造函数，这样就会申请多个指针
	//mAppFrame = new AppFrame();

	// 这个设置等价于在 Project Setting 中的设置
	std::string aaa = "aaa";
	//GetDefault<UGeneralProjectSettings>()->ProjectDisplayedTitle = UtilStr::ConvStdStr2FText(aaa);
	//GetDefault<UInputSettings>()->DefaultViewportMouseCaptureMode = EMouseCaptureMode::CaptureDuringMouseDown;
}

void UMyGameInstanceBase::Init()
{
	Super::Init();

	// UGameEngine 创建后，就创建 UGameInstance，这个是除 UGameEngine 外最早初始化的地方
	mAppFrame = new AppFrame();
	mAppFrame->initApp();
}

void UMyGameInstanceBase::Shutdown()
{
	Super::Shutdown();

	mAppFrame->quitApp();
}

void UMyGameInstanceBase::FinishDestroy()
{
	Super::FinishDestroy();
}

TSubclassOf<UOnlineSession> UMyGameInstanceBase::GetOnlineSessionClass()
{
	return UMyOnlineSession::StaticClass();
}
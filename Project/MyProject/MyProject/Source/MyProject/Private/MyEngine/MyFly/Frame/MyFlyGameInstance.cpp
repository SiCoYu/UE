#include "MyProject.h"
#include "MyFlyGameInstance.h"

#include "MyFlyOnlineSession.h"

UMyFlyGameInstance::UMyFlyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 逻辑指针不要放在构造函数中，因为脚本会调用一次构造函数，这样就会申请多个指针
	//mAppFrame = new AppFrame();

	// 这个设置等价于在 Project Setting 中的设置
	//std::string aaa = "aaa";
	//GetDefault<UGeneralProjectSettings>()->ProjectDisplayedTitle = UtilStr::ConvStdStr2FText(aaa);
	//GetDefault<UInputSettings>()->DefaultViewportMouseCaptureMode = EMouseCaptureMode::CaptureDuringMouseDown;
}

void UMyFlyGameInstance::Init()
{
	Super::Init();
}

void UMyFlyGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMyFlyGameInstance::FinishDestroy()
{
	Super::FinishDestroy();
}

TSubclassOf<UOnlineSession> UMyFlyGameInstance::GetOnlineSessionClass()
{
	return UMyFlyOnlineSession::StaticClass();
}
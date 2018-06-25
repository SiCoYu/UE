#include "MyProject.h"
#include "MyTomGameInstance.h"

#include "MyFlyOnlineSession.h"

UMyTomGameInstance::UMyTomGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 逻辑指针不要放在构造函数中，因为脚本会调用一次构造函数，这样就会申请多个指针
	//mAppFrame = new AppFrame();

	// 这个设置等价于在 Project Setting 中的设置
	//std::string aaa = "aaa";
	//GetDefault<UGeneralProjectSettings>()->ProjectDisplayedTitle = UtilStr::ConvStdStr2FText(aaa);
	//GetDefault<UInputSettings>()->DefaultViewportMouseCaptureMode = EMouseCaptureMode::CaptureDuringMouseDown;
}

void UMyTomGameInstance::Init()
{
	Super::Init();
}

void UMyTomGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMyTomGameInstance::FinishDestroy()
{
	Super::FinishDestroy();
}

TSubclassOf<UOnlineSession> UMyTomGameInstance::GetOnlineSessionClass()
{
	return UMyTomOnlineSession::StaticClass();
}
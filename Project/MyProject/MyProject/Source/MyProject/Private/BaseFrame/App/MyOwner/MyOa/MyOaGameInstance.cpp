#include "MyProject.h"
#include "MyTPGameInstance.h"

#include "MyTPOnlineSession.h"

UMyTPGameInstance::UMyTPGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 逻辑指针不要放在构造函数中，因为脚本会调用一次构造函数，这样就会申请多个指针
	//mAppFrame = new AppFrame();

	// 这个设置等价于在 Project Setting 中的设置
	//std::string aaa = "aaa";
	//GetDefault<UGeneralProjectSettings>()->ProjectDisplayedTitle = UtilStr::ConvStdStr2FText(aaa);
	//GetDefault<UInputSettings>()->DefaultViewportMouseCaptureMode = EMouseCaptureMode::CaptureDuringMouseDown;
}

void UMyTPGameInstance::Init()
{
	Super::Init();
}

void UMyTPGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMyTPGameInstance::FinishDestroy()
{
	Super::FinishDestroy();
}

TSubclassOf<UOnlineSession> UMyTPGameInstance::GetOnlineSessionClass()
{
	return UMyTPOnlineSession::StaticClass();
}
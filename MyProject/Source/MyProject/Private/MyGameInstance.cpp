#include "MyProject.h"
#include "MyGameInstance.h"

#include "AppFrame.h"
//#include "Ctx.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_appFrame = new AppFrame();
}

void UMyGameInstance::Init()
{
	Super::Init();
	m_appFrame->initApp();
}
#include "MyProject.h"
#include "MyProjectGameInstance.h"

#include "MyAppFrame.h"
#include "MyCtx.h"

UMyProjectGameInstance::UMyProjectGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_myAppFrame = new MyAppFrame();
}

void UMyProjectGameInstance::Init()
{
	Super::Init();
	MyCtx::getSingletonPtr()->setGameInstance(this);
	m_myAppFrame->initApp();
}
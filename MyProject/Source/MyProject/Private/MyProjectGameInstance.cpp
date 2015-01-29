#include "MyProject.h"
#include "MyProjectGameInstance.h"

#include "MyAppFrame.h"

UMyProjectGameInstance::UMyProjectGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_myAppFrame = new MyAppFrame();
}

void UMyProjectGameInstance::Init()
{
	Super::Init();

	m_myAppFrame->initApp();
}
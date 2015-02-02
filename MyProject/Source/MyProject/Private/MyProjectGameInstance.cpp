#include "MyProject.h"
#include "MyProjectGameInstance.h"

#include "AppFrame.h"
//#include "Ctx.h"

UMyProjectGameInstance::UMyProjectGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_appFrame = new AppFrame();
}

void UMyProjectGameInstance::Init()
{
	Super::Init();
	//Ctx::getSingletonPtr()->setGameInstance(this);
	m_appFrame->initApp();
}
#include "MyProject.h"
#include "MConsoleManager.h"

TAutoConsoleVariable<int32> UMConsoleManager::CVarTestCmd(
    TEXT("MyCmd.TestCmd"),
    2,
    TEXT("Defines Test.\n")
    TEXT("<=0: default\n")
    TEXT("  1: start\n")
    TEXT("  2: run\n")
    TEXT("  3: end"),
    ECVF_Scalability | ECVF_RenderThreadSafe);

UMConsoleManager::UMConsoleManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMConsoleManager::init()
{

}

void UMConsoleManager::dispose()
{

}

void UMConsoleManager::registerConsoleVariable()
{
	this->mTestCmd = IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("MyCmd.TestCmd"),
		TEXT("Defines Test.\n")
		TEXT("<=0: default\n")
		TEXT("  1: start\n")
		TEXT("  2: run\n")
		TEXT("  3: end"),
		// error C2338: You cannot use raw method delegates with UObjects.
		//FConsoleCommandDelegate::CreateRaw(this, &UMConsoleSys::myCmdHandle),
		FConsoleCommandDelegate::CreateUObject(this, &UMConsoleManager::myCmdHandle),
	   ECVF_Scalability | ECVF_RenderThreadSafe);
}

void UMConsoleManager::unregisterConsoleVariable()
{
	IConsoleManager::Get().UnregisterConsoleObject(this->mTestCmd);
}

void UMConsoleManager::myCmdHandle()
{

}
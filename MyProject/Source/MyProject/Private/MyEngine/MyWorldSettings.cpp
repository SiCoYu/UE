#include "MyProject.h"
#include "MyWorldSettings.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyGameMode.h"

AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 每一个关卡物理碰撞处理
	PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
	DefaultGameMode = AMyGameMode::StaticClass();	// 如果没有设置，就是用引擎设置的
}
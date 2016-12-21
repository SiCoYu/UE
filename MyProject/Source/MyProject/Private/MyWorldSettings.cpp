#include "MyProject.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyWorldSettings.h"

AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 每一个关卡物理碰撞处理
	PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
}
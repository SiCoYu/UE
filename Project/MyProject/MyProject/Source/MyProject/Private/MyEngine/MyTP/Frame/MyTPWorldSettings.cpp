#include "MyProject.h"
#include "MyTPWorldSettings.h"
#include "MyTPPhysicsCollisionHandler.h"
#include "MyTPGameMode.h"

AMyTPWorldSettings::AMyTPWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 每一个关卡物理碰撞处理
	this->PhysicsCollisionHandlerClass = UMyTPPhysicsCollisionHandler::StaticClass();
	this->DefaultGameMode = AMyTPGameMode::StaticClass();	// 如果没有设置，就是用引擎设置的
}
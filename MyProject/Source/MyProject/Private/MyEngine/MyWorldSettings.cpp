#include "MyProject.h"
#include "MyWorldSettings.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyGameMode.h"
#include "MyFlyGameMode.h"

AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 每一个关卡物理碰撞处理
	this->PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
	//this->DefaultGameMode = AMyGameMode::StaticClass();	// 如果没有设置，就是用引擎设置的
	this->DefaultGameMode = AMyFlyGameMode::StaticClass();
}
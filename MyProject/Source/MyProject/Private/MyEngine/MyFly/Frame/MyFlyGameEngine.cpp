#include "MyProject.h"
#include "MyFlyGameEngine.h"
#include "Common.h"
#include "MyFlyPhysicsCollisionHandler.h"
#include "MyAvoidanceManager.h"
#include "MyFlyLocalPlayer.h"

UMyEngine::UMyEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 全局物理碰撞处理
	this->PhysicsCollisionHandlerClass = UMyFlyPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyAvoidanceManager::StaticClass();
	// 等价于 MyProject\Config\DefaultEngine.ini 配置文件中的 LocalPlayerClassName 设置
	this->LocalPlayerClass = UMyFlyLocalPlayer::StaticClass();
}

void UMyEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
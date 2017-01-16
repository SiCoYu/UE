#include "MyProject.h"
#include "MyTPGameEngine.h"
#include "Common.h"
#include "MyTPPhysicsCollisionHandler.h"
#include "MyTPAvoidanceManager.h"
#include "MyTpLocalPlayer.h"

UMyTPGameEngine::UMyTPGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 全局物理碰撞处理
	this->PhysicsCollisionHandlerClass = UMyTPPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyTPAvoidanceManager::StaticClass();
	// 等价于 MyProject\Config\DefaultEngine.ini 配置文件中的 LocalPlayerClassName 设置
	this->LocalPlayerClass = UMyTpLocalPlayer::StaticClass();
}

void UMyTPGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
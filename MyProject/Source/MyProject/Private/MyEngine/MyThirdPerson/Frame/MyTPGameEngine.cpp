#include "MyProject.h"
#include "MyTPGameEngine.h"
#include "Common.h"
#include "MyTPPhysicsCollisionHandler.h"
#include "MyAvoidanceManager.h"
#include "MyTPLocalPlayer.h"

UMyTPGameEngine::UMyTPGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 全局物理碰撞处理
	PhysicsCollisionHandlerClass = UMyTPPhysicsCollisionHandler::StaticClass();
	AvoidanceManagerClass = UMyAvoidanceManager::StaticClass();
	// 等价于 MyProject\Config\DefaultEngine.ini 配置文件中的 LocalPlayerClassName 设置
	LocalPlayerClass = UMyTPLocalPlayer::StaticClass();
}

void UMyTPGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
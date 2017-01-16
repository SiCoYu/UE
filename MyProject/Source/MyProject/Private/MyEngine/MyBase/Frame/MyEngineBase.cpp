#include "MyProject.h"
#include "MyEngine.h"
#include "Common.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyAvoidanceManager.h"
#include "MyLocalPlayer.h"

UMyEngine::UMyEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 全局物理碰撞处理
	PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
	AvoidanceManagerClass = UMyAvoidanceManager::StaticClass();
	// 等价于 MyProject\Config\DefaultEngine.ini 配置文件中的 LocalPlayerClassName 设置
	LocalPlayerClass = UMyLocalPlayer::StaticClass();
}

void UMyEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);

	// 最早初始化的地方
	GEngineData->setMyEngine(this);
}
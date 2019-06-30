#include "MyProject.h"
#include "MyOaGameEngine.h"
#include "Prequisites.h"
#include "MyOaPhysicsCollisionHandler.h"
#include "MyOaAvoidanceManager.h"
#include "MyOaLocalPlayer.h"

UMyOaGameEngine::UMyOaGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 全局物理碰撞处理
	this->PhysicsCollisionHandlerClass = UMyOaPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyOaAvoidanceManager::StaticClass();
	// 等价于 MyProject\Config\DefaultEngine.ini 配置文件中的 LocalPlayerClassName 设置
	this->LocalPlayerClass = UMyOaLocalPlayer::StaticClass();
}

void UMyOaGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
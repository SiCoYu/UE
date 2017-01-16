#include "MyProject.h"
#include "MyTPGameEngine.h"
#include "Common.h"
#include "MyTPPhysicsCollisionHandler.h"
#include "MyAvoidanceManager.h"
#include "MyTPLocalPlayer.h"

UMyTPGameEngine::UMyTPGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ȫ��������ײ����
	PhysicsCollisionHandlerClass = UMyTPPhysicsCollisionHandler::StaticClass();
	AvoidanceManagerClass = UMyAvoidanceManager::StaticClass();
	// �ȼ��� MyProject\Config\DefaultEngine.ini �����ļ��е� LocalPlayerClassName ����
	LocalPlayerClass = UMyTPLocalPlayer::StaticClass();
}

void UMyTPGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
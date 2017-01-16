#include "MyProject.h"
#include "MyTPGameEngine.h"
#include "Common.h"
#include "MyTPPhysicsCollisionHandler.h"
#include "MyTPAvoidanceManager.h"
#include "MyTpLocalPlayer.h"

UMyTPGameEngine::UMyTPGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ȫ��������ײ����
	this->PhysicsCollisionHandlerClass = UMyTPPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyTPAvoidanceManager::StaticClass();
	// �ȼ��� MyProject\Config\DefaultEngine.ini �����ļ��е� LocalPlayerClassName ����
	this->LocalPlayerClass = UMyTpLocalPlayer::StaticClass();
}

void UMyTPGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
#include "MyProject.h"
#include "MyFlyGameEngine.h"
#include "Common.h"
#include "MyFlyPhysicsCollisionHandler.h"
#include "MyFlyAvoidanceManager.h"
#include "MyFlyLocalPlayer.h"

UMyFlyGameEngine::UMyFlyGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ȫ��������ײ����
	this->PhysicsCollisionHandlerClass = UMyFlyPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyFlyAvoidanceManager::StaticClass();
	// �ȼ��� MyProject\Config\DefaultEngine.ini �����ļ��е� LocalPlayerClassName ����
	this->LocalPlayerClass = UMyFlyLocalPlayer::StaticClass();
}

void UMyFlyGameEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
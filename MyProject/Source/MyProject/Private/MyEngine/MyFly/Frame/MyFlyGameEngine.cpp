#include "MyProject.h"
#include "MyFlyGameEngine.h"
#include "Common.h"
#include "MyFlyPhysicsCollisionHandler.h"
#include "MyAvoidanceManager.h"
#include "MyFlyLocalPlayer.h"

UMyEngine::UMyEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ȫ��������ײ����
	this->PhysicsCollisionHandlerClass = UMyFlyPhysicsCollisionHandler::StaticClass();
	this->AvoidanceManagerClass = UMyAvoidanceManager::StaticClass();
	// �ȼ��� MyProject\Config\DefaultEngine.ini �����ļ��е� LocalPlayerClassName ����
	this->LocalPlayerClass = UMyFlyLocalPlayer::StaticClass();
}

void UMyEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}
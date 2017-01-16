#include "MyProject.h"
#include "MyEngine.h"
#include "Common.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyAvoidanceManager.h"
#include "MyLocalPlayer.h"

UMyEngine::UMyEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ȫ��������ײ����
	PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
	AvoidanceManagerClass = UMyAvoidanceManager::StaticClass();
	// �ȼ��� MyProject\Config\DefaultEngine.ini �����ļ��е� LocalPlayerClassName ����
	LocalPlayerClass = UMyLocalPlayer::StaticClass();
}

void UMyEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);

	// �����ʼ���ĵط�
	GEngineData->setMyEngine(this);
}
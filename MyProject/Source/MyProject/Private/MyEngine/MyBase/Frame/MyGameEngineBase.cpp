#include "MyProject.h"
#include "MyGameEngineBase.h"
#include "Common.h"

UMyGameEngineBase::UMyGameEngineBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UMyGameEngineBase::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);

	// 最早初始化的地方
	GEngineData->setMyEngine(this);
}
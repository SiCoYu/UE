#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS(config = Game)
class AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaSeconds) override;
	// APawn 才有这个接口， AActor 没有这个接口
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponentParam) override;
};
#pragma once

#include "Components/ActorComponent.h"
#include "AppRoot.generated.h"

UCLASS()
class UAppRoot : public UActorComponent
{
	GENERATED_BODY()

public:
	UAppRoot(const FObjectInitializer& PCIP);

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
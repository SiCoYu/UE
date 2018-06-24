#pragma once

#include "AuxUserData.h"
#include "AppRoot.generated.h"

UCLASS()
class UAppRoot : public UAuxUserData
{
	GENERATED_BODY()

public:
	UAppRoot(const FObjectInitializer& PCIP);

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
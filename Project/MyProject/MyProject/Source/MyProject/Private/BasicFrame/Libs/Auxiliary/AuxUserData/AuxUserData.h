#pragma once

#include "Components/ActorComponent.h"
#include "AuxUserData.generated.h"

/**
 * @brief UAuxUserData， 组件根节点，在组件中保存用户数据
 */
UCLASS()
class UAuxUserData : public UActorComponent
{
	GENERATED_BODY()

public:
	UAuxUserData(const FObjectInitializer& PCIP);

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
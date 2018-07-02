#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuxActorUserData.generated.h"

/**
 * @brief UAuxUserData， 组件根节点，在组件中保存用户数据
 * @meta UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) ，没有这个，在编辑器中的 [AddComponent] 看不到组件
 */
UCLASS( ClassGroup = (MyUserData), meta = (BlueprintSpawnableComponent) )
class UAuxActorUserData : public UActorComponent
{
	GENERATED_BODY()

public:
	UAuxActorUserData(const FObjectInitializer& PCIP);

public:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginDestroy() override;
};
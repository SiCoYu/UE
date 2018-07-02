#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuxActorUserData.generated.h"

/**
 * @brief UAuxUserData�� ������ڵ㣬������б����û�����
 * @meta UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) ��û��������ڱ༭���е� [AddComponent] ���������
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
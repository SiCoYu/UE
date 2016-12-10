#pragma once

#include "Components/StaticMeshComponent.h"
#include "MyBPStaticMeshComp.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 */

UCLASS(ClassGroup = Solus, meta = (BlueprintSpawnableComponent))
class UMyBPStaticMeshComp : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()

	//SkelMeshComp
protected:
	//Init
	virtual void InitializeComponent() OVERRIDE;

	//Tick
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) OVERRIDE;
};
#pragma once

#include "Components/StaticMeshComponent.h"
#include "MyBPStaticMeshComponent.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 */

UCLASS(ClassGroup = Solus, meta = (BlueprintSpawnableComponent))
class UMyBPStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()

public:
	//UMyBPStaticMeshComponent(class FObjectInitializer const& PCIP);

	//SkelMeshComp
protected:
	/**
	//InitEngine\Source\Runtime\Core\Public\HAL\Platform.h
	// Legacy method modifier macros.  You shouldn't use these macros in modern code.  Use the built-in keyword directly.
	#ifndef OVERRIDE
	#define OVERRIDE \
	EMIT_DEPRECATED_WARNING_MESSAGE("OVERRIDE macro is deprecated. Please use override keyword instead.") \
	override
	#endif
	*/
	//virtual void InitializeComponent() OVERRIDE;
	virtual void InitializeComponent() override;

	//Tick
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) OVERRIDE;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
#pragma once

#include "GameFramework/Actor.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/NavMovementComponent.h"
#include "MTestStaticConstructorAndLoad.generated.h"

class UStaticMesh;

/**
 * @brief Creating component subobjects and attaching them to the actor's hierarchy can also be done inside of the constructor. When spawning an actor, its components will be cloned from the CDO. In order to ensure that components are always created, destroyed, and properly garbage-collected, a pointer to every component created in the constructor should be stored in a UPROPERTY of the owning class. 
 * @ref https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Classes/index.html
 */

UCLASS()
class AMTestStaticConstructorAndLoad : public AActor
{
    GENERATED_BODY()

public:
	AMTestStaticConstructorAndLoad();
	AMTestStaticConstructorAndLoad(const FObjectInitializer& PCIP = FObjectInitializer::Get());

	UPROPERTY()
	TSubclassOf<UNavMovementComponent> NavMeshClass;

    UPROPERTY()
	UStaticMesh* StaticMesh;
};

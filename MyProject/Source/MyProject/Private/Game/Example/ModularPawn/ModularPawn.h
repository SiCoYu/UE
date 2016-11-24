#pragma once

#include "MyProject.h"
#include "ModularPawn.generated.h"

/**
* @brief https://wiki.unrealengine.com/Modular_Pawn
*/
UCLASS(config = Game)
class AModularPawn : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/**
	*  The skeletal mesh used for the body.
	*  Mesh (inherited from ACharacter) will act as characters head.
	*/
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	TSubobjectPtr<class USkeletalMeshComponent> Body;

	/**
	*  Name of the BodyComponentName.
	*  Use this name if you want to prevent creation of the component (with PCIP.DoNotCreateDefaultSubobject).
	*/
	static FName BodyComponentName;

	/**
	*  The skeletal mesh used for the legs.
	*  Mesh (inherited from ACharacter) will act as characters head.
	*/
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
		TSubobjectPtr<class USkeletalMeshComponent> Legs;

	/**
	*  Name of the BodyComponentName.
	*  Use this name if you want to prevent creation of the component (with PCIP.DoNotCreateDefaultSubobject).
	*/
	static FName LegsComponentName;
};
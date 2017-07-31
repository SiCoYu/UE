#pragma once

#include "MyProject.h"
#include "DeferAttachToSocketActor.generated.h"

/**
* @brief https://wiki.unrealengine.com/Actor_Components,_Making_Native_%26_Deferred_Attached_to_Socket
*/

UCLASS(config = Game)
class ADeferAttachToSocketActor : public ACharacter
{
	GENERATED_BODY()

private:
	// #define TSubobjectPtr \
	//EMIT_DEPRECATED_WARNING_MESSAGE("TSubobjectPtr is deprecated and should no longer be used. Please use pointers instead.") \
	//TSubobjectPtrDeprecated
	// TSubobjectPtr 不要再使用了，或者 TSubobjectPtrDeprecated ，或者直接使用指针
	//TSubobjectPtr<UStaticMeshComponent> JoyfulControl;
	UStaticMeshComponent* JoyfulControl;
	UStaticMesh* AssetSM_JoyControl;

	FORCEINLINE void SetupSMComponentsWithCollision(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;
		//~~~~~~~~

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Block);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Block);
		Comp->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Block);
		Comp->SetHiddenInGame(false);
	}

public:
	ADeferAttachToSocketActor(const FObjectInitializer& ObjectInitializer);
};
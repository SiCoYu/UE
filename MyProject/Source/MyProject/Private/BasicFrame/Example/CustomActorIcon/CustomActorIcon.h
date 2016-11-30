#pragma once

#include "GameFramework/Actor.h"
#include "CustomActorIcon.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Add_in_editor_Icon_to_your_Custom_Actor
 */
UCLASS(config=Game)
class ACustomActorIcon : public AActor
{
	GENERATED_BODY()
	//virtual void BeginPlay() override;
	virtual void BeginPlay();

	UPROPERTY()
	// A UBillboardComponent to hold Icon sprite
	// TSubobjectPtr is deprecated and should no longer be used. Please use pointers instead.
	//TSubobjectPtr<UBillboardComponent> SpriteComponent;
	UBillboardComponent* SpriteComponent;

	// Icon sprite
	UTexture2D* SpriteTexture;

public:
	ACustomActorIcon(const FObjectInitializer& ObjectInitializer);
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AuxSceneUserData.generated.h"


UCLASS( ClassGroup=(MyUserData), meta=(BlueprintSpawnableComponent) )
class UAuxSceneUserData : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAuxSceneUserData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};

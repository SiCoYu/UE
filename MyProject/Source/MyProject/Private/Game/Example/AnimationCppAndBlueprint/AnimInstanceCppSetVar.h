// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyProject.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceCppSetVar.generated.h"

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class UAnimInstanceCppSetVar : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

	/** Left Lower Leg Offset From Ground, Set in Character.cpp Tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPlacement)
	FVector SkelControl_LeftLowerLegPos;

	/** Left Foot Rotation, Set in Character.cpp Tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPlacement)
		FRotator SkelControl_LeftFootRotation;

	/** Left Upper Leg Offset, Set in Character.cpp Tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootPlacement)
		FVector SkelControl_LeftUpperLegPos;
};
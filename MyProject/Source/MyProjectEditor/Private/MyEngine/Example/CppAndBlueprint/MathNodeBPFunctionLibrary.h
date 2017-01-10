// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphSchema.h"
#include "MathNodeBPFunctionLibrary.generated.h"

/**
 * Created by Gareth "G-Rath" Jones, 06/04/2014L
 */
UCLASS()
class UMathNodeBPFunctionLibrary : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

public:

	/*
	* Returns a random unit vector, uniformly distributed, within the specified cone.
	* HorizontalConeHalfAngleRad is the half-angle of cone, in radians.  Returns a normalized vector.
	*
	* If bIsSquished is true then it creates a random cone with different angle limits in the Y and Z axes.
	* Set by HorizontalConeHalfAngleRad and VerticalConeHalfAngleRad respectively
	*	Otherwise only HorizontalConeHalfAngleRad is used.
	*
	* Assumes world Y and Z, although this could be extended to handle arbitrary rotations.
	*/
	// LogCompile:Error: Remapping old metadata key 'FriendlyName' to new key 'DisplayName', please update the declaration.
	//UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", FriendlyName = "Random VCone", CompactNodeTitle = "RanVCone", Keywords = "random vector cone radians"), Category = Math)
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Random VCone", CompactNodeTitle = "RanVCone", Keywords = "random vector cone radians"), Category = Math)
	static FVector VRandomConeFromRad(const FVector& Dir, float HorizontalConeHalfAngleRad, bool bIsSquished, float VerticalConeHalfAngleRad);

	/*
	* Returns a random unit vector, uniformly distributed, within the specified cone.
	* HorizontalConeHalfAngleDeg is the half-angle of cone, in degrees.  Returns a normalized vector.
	*
	* If bIsSquished is true then it creates a random cone with different angle limits in the Y and Z axes.
	* Set by HorizontalConeHalfAngleDeg and VerticalConeHalfAngleDeg respectively.
	*	Otherwise only HorizontalConeHalfAngleDeg is used.
	*
	* Assumes world Y and Z, although this could be extended to handle arbitrary rotations.
	*/
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Random VCone From Degrees", CompactNodeTitle = "RanVConeDeg", Keywords = "random vector cone degrees"), Category = Math)
	static FVector VRandomConeFromDeg(const FVector& Dir, float HorizontalConeHalfAngleDeg, bool bIsSquished, float VerticalConeHalfAngleDeg);

	/** Convets a angle in degrees into radians */
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Convert Degrees to Radians", CompactNodeTitle = "DegToRad", Keywords = "convert radians degrees"), Category = Math)
	static float FDegToRad(float AngleInDegrees);

	/** Convets a angle in radians into degrees */
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Convert Radians to Degrees", CompactNodeTitle = "RadToDeg", Keywords = "convert radians degrees"), Category = Math)
	static float FRadToDeg(float AngleInRadians);

	/**
	*	Checks if two floating point numbers are nearly equal.
	*	@param A				First number to compare
	*	@param B				Second number to compare
	*	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	*	@return					true if A and B are nearly equal
	*/
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Is float nearly equal", CompactNodeTitle = "IsNear=", Keywords = "nearly equal float"), Category = Math)
	static bool IsNearlyEqual(float A, float B, float ErrorTolerance);

	/**
	*	Checks if a floating point number is nearly zero.
	*	@param Value			Number to compare
	*	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	*	@return					true if Value is nearly zero
	*/
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Is float nearly zero", CompactNodeTitle = "IsNear0", Keywords = "nearly zero float"), Category = Math)
	static bool IsNearlyZero(float Value, float ErrorTolerance);

	/**
	*	Checks whether a number is a power of two.
	*	@param Value	Number to check
	*	@return			true if Value is a power of two
	*/
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Is power of two", CompactNodeTitle = "IsPowOf2", Keywords = "is power two"), Category = Math)
	static bool IsPowerOfTwo(float Value);
};
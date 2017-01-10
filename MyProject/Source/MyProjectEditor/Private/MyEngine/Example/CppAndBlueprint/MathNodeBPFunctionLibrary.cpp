#include "MyProjectEditor.h" //Change this to your project's header file (Its the file thats got the same name as your project and ends with .h)
#include "UnrealMathVectorCommon.h"
#include "MathNodeBPFunctionLibrary.h"

#define SMALL_NUMBER		(1.e-8f)

UMathNodeBPFunctionLibrary::UMathNodeBPFunctionLibrary(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

FVector UMathNodeBPFunctionLibrary::VRandomConeFromRad(const FVector& Dir, float HorizontalConeHalfAngleRad, bool bIsSquished, float VerticalConeHalfAngleRad)
{
	if (bIsSquished)
		return FMath::VRandCone(Dir, HorizontalConeHalfAngleRad, VerticalConeHalfAngleRad);
	else
		return FMath::VRandCone(Dir, HorizontalConeHalfAngleRad);
}

FVector UMathNodeBPFunctionLibrary::VRandomConeFromDeg(const FVector& Dir, float HorizontalConeHalfAngleDeg, bool bIsSquished, float VerticalConeHalfAngleDeg)
{
	if (bIsSquished)
		return FMath::VRandCone(Dir, FMath::DegreesToRadians(HorizontalConeHalfAngleDeg), FMath::DegreesToRadians(VerticalConeHalfAngleDeg));
	else
		return FMath::VRandCone(Dir, FMath::DegreesToRadians(HorizontalConeHalfAngleDeg));
}

float UMathNodeBPFunctionLibrary::FDegToRad(float AngleInDegrees)
{
	return FMath::DegreesToRadians(AngleInDegrees);
}

float UMathNodeBPFunctionLibrary::FRadToDeg(float AngleInRadians)
{
	return FMath::RadiansToDegrees(AngleInRadians);
}

bool UMathNodeBPFunctionLibrary::IsNearlyEqual(float A, float B, float ErrorTolerance = SMALL_NUMBER)
{
	return FMath::IsNearlyEqual(A, B, ErrorTolerance);
}

bool UMathNodeBPFunctionLibrary::IsNearlyZero(float Value, float ErrorTolerence = SMALL_NUMBER)
{
	return FMath::IsNearlyZero(Value, ErrorTolerence);
}

bool UMathNodeBPFunctionLibrary::IsPowerOfTwo(float Value)
{
	return FMath::IsPowerOfTwo(Value);
}
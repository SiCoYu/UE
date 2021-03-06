// UE4 4.17 : error : Expected MathNodeBPFunctionLibrary.h to be first header included.
//#include "MyProjectEditor.h" //Change this to your project's header file (Its the file thats got the same name as your project and ends with .h)
#include "MathNodeBPFunctionLibrary.h"
#include "UnrealMathVectorCommon.h"

#define SMALL_NUMBER		(1.e-8f)

UMathNodeBPFunctionLibrary::UMathNodeBPFunctionLibrary(const class FObjectInitializer& PCIP)
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
	// error C2296: '&': illegal, left operand has type 'float'
	//return FMath::IsPowerOfTwo(Value);
	return FMath::IsPowerOfTwo((int)Value);
}
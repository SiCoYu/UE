#include "MyProject.h"
#include "CoordinateMappingActor.h"

ACoordinateMappingActor::ACoordinateMappingActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void ALeapMotionHandActor::UpdateBonesOne(float DeltaSeconds)
{
	if (BoneActors.Num() == 0) { return; }

	float CombinedScale = GetCombinedScale();

	FLeapMotionDevice* Device = FLeapMotionControllerPlugin::GetLeapDeviceSafe();
	if (Device && Device->IsConnected())
	{
		int BoneArrayIndex = 0;
		for (ELeapBone LeapBone = bShowArm ? ELeapBone::Forearm : ELeapBone::Palm; LeapBone <= ELeapBone::Finger4Tip; ((int8&)LeapBone)++)
		{
			FVector TargetPosition;
			FRotator TargetOrientation;

			bool Success = Device->GetBonePostionAndOrientation(HandId, LeapBone, TargetPosition, TargetOrientation);
			if (Success)
			{
				// Offset target position & rotation by the SpawnReference actor's transform
				const FQuat RefQuat = GetRootComponent()->GetComponentQuat();
				TargetPosition = RefQuat * TargetPosition * CombinedScale + GetRootComponent()->GetComponentLocation();
				TargetOrientation = (RefQuat * TargetOrientation.Quaternion()).Rotator();

				// Get current position & rotation
				ALeapMotionBoneActor* BoneActor = BoneActors[BoneArrayIndex++];
				UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(BoneActor->GetRootComponent());
				if (PrimitiveComponent)
				{
					PrimitiveComponent->SetRelativeLocationAndRotation(TargetPosition, TargetOrientation, true);
				}
			}
		}
	}
}

void ALeapMotionHandActor::UpdateBonesTwo(float DeltaSeconds)
{
	//MODIFICATION.This array to record each bone's position. The first bone's position is boneLocationData[0]
	TArray<FVector> boneLocationData;

	if (BoneActors.Num() == 0) { return; }

	float CombinedScale = GetCombinedScale();

	FLeapMotionDevice* Device = FLeapMotionControllerPlugin::GetLeapDeviceSafe();
	if (Device && Device->IsConnected())
	{
		int BoneArrayIndex = 0;
		for (ELeapBone LeapBone = bShowArm ? ELeapBone::Forearm : ELeapBone::Palm; LeapBone <= ELeapBone::Finger4Tip; ((int8&)LeapBone)++)
		{
			FVector TargetPosition;
			FRotator TargetOrientation;

			bool Success = Device->GetBonePostionAndOrientation(HandId, LeapBone, TargetPosition, TargetOrientation);
			if (Success)
			{
				// Offset target position & rotation by the SpawnReference actor's transform
				const FQuat RefQuat = GetRootComponent()->GetComponentQuat();
				TargetPosition = RefQuat * TargetPosition * CombinedScale + GetRootComponent()->GetComponentLocation();
				TargetOrientation = (RefQuat * TargetOrientation.Quaternion()).Rotator();

				// Get current position & rotation
				ALeapMotionBoneActor* BoneActor = BoneActors[BoneArrayIndex++];
				UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(BoneActor->GetRootComponent());
				if (PrimitiveComponent)
				{
					//MODIFICATION. you can substitute 15 with the factor you like 
					PrimitiveComponent->SetWorldLocationAndRotation(TargetPosition + FVector(boneLocationData[0].X * 15, boneLocationData[0].Y * 15, boneLocationData[0].Z * 15), TargetOrientation, true);

				}
			}
		}
	}
}
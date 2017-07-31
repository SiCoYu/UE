#include "MyProject.h"
#include "MyPlayerCameraManagerBase.h"

AMyPlayerCameraManagerBase::AMyPlayerCameraManagerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NormalFOV = 90.0f;
	TargetingFOV = 60.0f;
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
	bAlwaysApplyModifiers = true;
}

void AMyPlayerCameraManagerBase::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
}

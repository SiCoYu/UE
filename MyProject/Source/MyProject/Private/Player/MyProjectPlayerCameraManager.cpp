#include "MyProject.h"
#include "Player/MyProjectCameraManager.h"

AMyProjectCameraManager::AMyProjectCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NormalFOV = 90.0f;
	TargetingFOV = 60.0f;
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
	bAlwaysApplyModifiers = true;
}

void AMyProjectCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
}

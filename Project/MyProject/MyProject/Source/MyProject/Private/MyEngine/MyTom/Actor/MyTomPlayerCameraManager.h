#pragma once

#include "MyPlayerCameraManagerBase.h"
#include "MyTomPlayerCameraManager.generated.h"

UCLASS()
class AMyTomPlayerCameraManager : public AMyPlayerCameraManagerBase
{
	GENERATED_UCLASS_BODY()

public:

	/** normal FOV */
	float NormalFOV;

	/** targeting FOV */
	float TargetingFOV;

	/** After updating camera, inform pawn to update 1p mesh to match camera's location&rotation */
	virtual void UpdateCamera(float DeltaTime) override;
};
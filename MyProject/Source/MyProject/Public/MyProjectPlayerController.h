#pragma once

#include "MyProject.h"
#include "MyProjectPlayerController.generated.h"

UCLASS(Within=Engine, transient, config=Engine)
class AMyProjectPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	//public:
	//	AMyProjectPlayerController(const FObjectInitializer& ObjectInitializer)
};
#pragma once

#include "MyProject.h"
#include "MyViewportClient.generated.h"

UCLASS(Within=Engine, transient, config=Engine)
class UMyViewportClient : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()

//public:
//	UMyViewportClient(const FObjectInitializer& ObjectInitializer)
};
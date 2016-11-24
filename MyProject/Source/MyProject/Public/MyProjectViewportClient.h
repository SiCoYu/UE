#pragma once

#include "MyProject.h"
#include "MyProjectViewportClient.generated.h"

UCLASS(Within=Engine, transient, config=Engine)
class UMyProjectViewportClient : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()

//public:
//	UMyProjectViewportClient(const FObjectInitializer& ObjectInitializer)
};
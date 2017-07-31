#pragma once

#include "UMGForm.h"
#include "UITestUMG.generated.h"

UCLASS(config = Game)
class UUITestUMG : public UUMGForm
{
	GENERATED_BODY()

public:
	UUITestUMG(const FObjectInitializer& ObjectInitializer);
};
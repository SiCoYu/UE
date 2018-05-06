#pragma once

#include "UMGForm.h"
#include "UITestUMG.generated.h"

UCLASS(config = Game)
class UUiTestUMG : public UUMGForm
{
	GENERATED_BODY()

public:
	UUiTestUMG(const FObjectInitializer& ObjectInitializer);
};
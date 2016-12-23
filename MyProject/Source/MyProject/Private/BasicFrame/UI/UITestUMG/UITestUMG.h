#pragma once

#include "SlateForm.h"
#include "UITestUMG.generated.h"

UCLASS(config = Game)
class UUITestUMG : public USlateForm
{
	GENERATED_BODY()

public:
	UUITestUMG(const FObjectInitializer& ObjectInitializer);
};
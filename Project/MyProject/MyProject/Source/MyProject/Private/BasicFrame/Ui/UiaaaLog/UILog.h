#pragma once

#include "SlateForm.h"
#include "UILog.generated.h"

UCLASS(config = Game)
class UUILog : public USlateForm
{
	GENERATED_BODY()

public:
	UUILog(const FObjectInitializer& ObjectInitializer);
};
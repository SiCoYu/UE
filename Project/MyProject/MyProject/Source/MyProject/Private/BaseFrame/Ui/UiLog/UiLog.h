#pragma once

#include "SlateForm.h"
#include "UILog.generated.h"

UCLASS(config = Game)
class UUiLog : public USlateForm
{
	GENERATED_BODY()

public:
	UUiLog(const FObjectInitializer& ObjectInitializer);
};
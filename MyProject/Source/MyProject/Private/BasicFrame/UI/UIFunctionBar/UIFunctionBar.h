#pragma once

#include "UMGForm.h"
#include "UIFunctionBar.generated.h"

UCLASS(config = Game)
class UUIFunctionBar : public UUMGForm
{
	GENERATED_BODY()

public:
	UUIFunctionBar(const FObjectInitializer& ObjectInitializer);

public:
	virtual void onReady() override;
};
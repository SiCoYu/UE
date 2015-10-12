#pragma once

#include "UMGForm.h"
#include "UITestCanvas.generated.h"

UCLASS(config = Game)
class UUITestCanvas : public UUMGForm
{
	GENERATED_BODY()

public:
	UUITestCanvas(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

	virtual void onReady();
};
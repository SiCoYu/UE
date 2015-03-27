#pragma once

#include "UMGForm.h"
#include "UIPack.generated.h"

UCLASS(config = Game)
class UUIPack : public UUMGForm
{
	GENERATED_BODY()

public:
	UUIPack(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

	virtual void onReady();
};
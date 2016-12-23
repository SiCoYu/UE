#pragma once

#include "Form.h"
#include "UMGForm.generated.h"

UCLASS(config = Game)
class UUMGForm : public UForm
{
	GENERATED_BODY()

public:
	UUMGForm(const FObjectInitializer& ObjectInitializer);

	// https://wiki.unrealengine.com/Extend_UserWidget_for_UMG_Widgets
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My New User Widget")
	FString MyNewWidgetName;
};
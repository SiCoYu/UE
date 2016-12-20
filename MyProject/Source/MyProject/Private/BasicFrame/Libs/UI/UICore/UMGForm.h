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

	// https ://wiki.unrealengine.com/UMG_Previewing_custom_UserWidgets_in_realtime
public:
	/**
	* This is called after a widget is constructed and properties are synchronized.
	* It can also be called by the editor to update modified state.
	* Override this event in blueprint to update the widget after a default property is modified.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "User Interface")
	void OnSynchronizeProperties();

	virtual void SynchronizeProperties() override;
};
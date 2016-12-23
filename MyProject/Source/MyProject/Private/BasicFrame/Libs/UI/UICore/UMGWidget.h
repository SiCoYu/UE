#pragma once

#include "Blueprint/UserWidget.h"	// UUserWidget
#include "Templates/SubclassOf.h"		// TSubclassOf
#include "UMGWidget.generated.h"

UCLASS(config=Game)
class UUMGWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TSubclassOf<class UUserWidget>  mWidgetClass;
	UUserWidget* mUiRoot;      // ui 根节点

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
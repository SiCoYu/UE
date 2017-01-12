#pragma once

#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/GraphEditor/Private/GraphEditorCommon.h"
#include "Containers/Array.h"	// TArray
#include "Containers/UnrealString.h"	// FString
#include "Templates/SharedPointer.h"	// TSharedPtr
#include "Widgets/SUserWidget.h"	// FArguments
#include "SlateBasics.h"
#include "Editor/GraphEditor/Public/SGraphPin.h"
#include "SlateCore.h"

/**
 * @brief https://wiki.unrealengine.com/How_To_Create_Custom_Blueprint_Pin
 First you will need Editor module in your plugin/game project. You can find information how to add it here:

 https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 */

class SGAAttributePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGAAttributePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

//public:
//	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//	//this override is used to display slate widget used forcustomization.
//	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
//	void OnAttributeSelected(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
//private:
//	TArray<TSharedPtr<FString>> AttributesList;
};
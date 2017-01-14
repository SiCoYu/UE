#pragma once

#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/GraphEditor/Private/GraphEditorCommon.h"
#include "Containers/Array.h"	// TArray
#include "Containers/UnrealString.h"	// FString
#include "Templates/SharedPointer.h"	// TSharedPtr
#include "Widgets/SUserWidget.h"	// FArguments
#include "SlateBasics.h"
//#include "SGraphPin.h"
#include "Editor/GraphEditor/Public/SGraphPin.h"
#include "SlateCore.h"
#include "Editor/UnrealEd/Public/EdGraphUtilities.h"
#include "Editor/UnrealEd/Public/GraphEditor.h"

#include "Widgets/Input/STextComboBox.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraph.h"
#include "EdGraphUtilities.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"

/**
 * @brief https://wiki.unrealengine.com/How_To_Create_Custom_Blueprint_Pin
 First you will need Editor module in your plugin/game project. You can find information how to add it here:

 https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 https://wiki.unrealengine.com/How_To_Create_Custom_Blueprint_Pin
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
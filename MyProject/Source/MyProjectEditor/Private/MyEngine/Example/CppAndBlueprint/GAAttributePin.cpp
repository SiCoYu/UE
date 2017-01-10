#include "MyProjectEditor.h"
#include "KismetEditorUtilities.h"

#include "STextComboBox.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "GAAttributePin.h"

void SGAAttributePin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	AttributesList.Empty();

	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}
TSharedRef<SWidget>	SGAAttributePin::GetDefaultValueWidget()
{
	//AttributesList.Empty();
	return	SNew(STextComboBox) //note you can display any widget here
		.OptionsSource(&AttributesList)
		.OnSelectionChanged(this, &SGAAttributePin::OnAttributeSelected);

}
void SGAAttributePin::OnAttributeSelected(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	//FString CurrentValue = GraphPinObj->GetDefaultAsString();
	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();
	FString attribute = *ItemSelected;
	if (CurrentDefaultValue.IsEmpty())
	{
		CurrentDefaultValue = FString(TEXT("()"));
	}
	//here we construct, setter for value in struct.
	//open it with (
	FString AttributeString = TEXT("(");
	if (!attribute.IsEmpty())
	{
		//now set here proerty name from USTRUCT(), \" - will add opening "
		// so it will look like AttributeName="
		AttributeString += TEXT("AttributeName=\"");
		//add value you want to set to your property"
		AttributeString += attribute;
		//close with "
		AttributeString += TEXT("\"");
	}
	//and at last add ) so it will look like (AttributeName="Value");
	AttributeString += TEXT(")");
	//and here we set our value to parameter if it different than last one.
	if (!CurrentDefaultValue.Equals(AttributeString))
	{
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, AttributeString);
	}
}
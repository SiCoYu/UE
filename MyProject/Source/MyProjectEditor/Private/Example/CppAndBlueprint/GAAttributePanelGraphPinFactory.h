#pragma once
#include "SlateBasics.h"
#include "GAGlobalTypes.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"
#include "GAAttributePanelGraphPinFactory.h"
#include "GAAttributePin.h"
#include "EdGraphUtilities.h"

/**
 * @brief https://wiki.unrealengine.com/How_To_Create_Custom_Blueprint_Pin
 First you will need Editor module in your plugin/game project. You can find information how to add it here:

 https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 */

class FGAAttributePanelGraphPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
	{
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
		/*
		Check if pin is struct, and then check if that pin is of struct type we want customize
		*/
		if (InPin->PinType.PinCategory == K2Schema->PC_Struct
			&& InPin->PinType.PinSubCategoryObject == FGAAttribute::StaticStruct())
		{
			return SNew(SGAAttributePin, InPin); //and return our customized pin widget ;).
		}
		return nullptr;
	}
};
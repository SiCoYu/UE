#pragma once

#include "AnimGraphNode_Base.h"		// UAnimGraphNode_Base
#include "AnimGraphDefinitions.h"
#include "Kismet2/BlueprintEditorUtils.h"

#include "AnimGraphNode_NameOfYourNode.generated.h"

/**
* @brief https://wiki.unrealengine.com/Animation_Nodes,_Code_for_How_to_Create_Your_Own
*/

//Whole point of this is to be wrapper for node struct
//	so it depends on it, and that node must compile first
//	for type to be recognized

// The dependsOn specifier is deprecated. Please use #include "ClassHeaderFilename.h" instead.
//UCLASS(MinimalAPI, dependson = FAnimNode_NameOfYourNode)
UCLASS(MinimalAPI)
class UAnimGraphNode_NameOfYourNode : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_NameOfYourNode Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	// End of UEdGraphNode interface

protected:
	virtual FString GetControllerDescription() const;
};
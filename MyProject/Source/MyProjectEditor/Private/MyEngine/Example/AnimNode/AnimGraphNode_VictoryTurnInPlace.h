#pragma once

#include "AnimGraphNode_Base.h"	// UAnimGraphNode_Base
#include "AnimGraphDefinitions.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "AnimGraphNode_VictoryTurnInPlace.generated.h"

class FAnimNode_VictoryTurnInPlace;

//Whole point of this is to be wrapper for node struct
//		so it depends on it, and that node must compile first
//		for type to be recognized

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Entire_Source_for_a_Turn_In_Place_Node
 */

// The dependsOn specifier is deprecated. Please use #include "ClassHeaderFilename.h" instead.
//UCLASS(MinimalAPI, dependson = FAnimNode_VictoryTurnInPlace)
UCLASS(MinimalAPI)
class UAnimGraphNode_VictoryTurnInPlace : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_VictoryTurnInPlace* Node;

public:
	// UEdGraphNode interface
	virtual FString GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	// End of UEdGraphNode interface

protected:
	// UAnimGraphNode_SkeletalControlBase interface
	virtual FString GetControllerDescription() const;
	// End of UAnimGraphNode_SkeletalControlBase interface
};
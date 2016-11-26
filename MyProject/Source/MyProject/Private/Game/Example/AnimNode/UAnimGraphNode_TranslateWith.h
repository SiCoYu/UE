// Created by Chance_07 2014
#pragma once

#include "AnimGraphNode_Base.h"
#include "AnimNode_TranslateWith.h"
#include "AnimGraphNode_TranslateWith.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */

UCLASS(MinimalAPI, dependson = AnimNode_TranslateWith)
class UAnimGraphNode_TranslateWith : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(EditAnywhere, Category = SkeletalControl)
		FAnimNode_TranslateWith Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const OVERRIDE;
	virtual FString GetTooltip() const OVERRIDE;
	virtual FString GetNodeCategory() const OVERRIDE;
	virtual FLinearColor GetNodeTitleColor() const OVERRIDE;
	virtual void CreateOutputPins() OVERRIDE;
	// End of UEdGraphNode interface

protected:
	virtual FText GetControllerDescription() const;

};
#pragma once

#include "AnimGraphNode_Base.h"	// UAnimGraphNode_Base
#include "AnimGraphNode_TranslateWith.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */

// error : The dependsOn specifier is deprecated. Please use #include "ClassHeaderFilename.h" instead.
//UCLASS(MinimalAPI, dependson = AnimNode_TranslateWith)
UCLASS()
class UAnimGraphNode_TranslateWith : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	UAnimGraphNode_TranslateWith* Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FString GetTooltip() const override;
	virtual FString GetNodeCategory() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void CreateOutputPins() override;
	// End of UEdGraphNode interface

protected:
	virtual FText GetControllerDescription() const;
};
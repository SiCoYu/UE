// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

//#include "MyProjectEditor.h"
#include "AnimGraphNode_NameOfYourNode.h"
//#include "UtilStr.h"

/////////////////////////////////////////////////////
// UAnimGraphNode_NameOfYourNode

UAnimGraphNode_NameOfYourNode::UAnimGraphNode_NameOfYourNode(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//Title Color!
FLinearColor UAnimGraphNode_NameOfYourNode::GetNodeTitleColor() const
{
	return FLinearColor(0, 12, 12, 1);
}

//Node Category
FString UAnimGraphNode_NameOfYourNode::GetNodeCategory() const
{
	return FString("Anim Node Category");
}
FString UAnimGraphNode_NameOfYourNode::GetControllerDescription() const
{
	return TEXT(" Your Anim node Title ");
}

FText UAnimGraphNode_NameOfYourNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	//FString Result = *GetControllerDescription();
	//Result += (TitleType == ENodeTitleType::ListView) ? TEXT("") : TEXT("\n");
	//return UtilStr::ConvFString2FText(Result);

	FString tmp = "Template";
	return FText::FromString(tmp);
}
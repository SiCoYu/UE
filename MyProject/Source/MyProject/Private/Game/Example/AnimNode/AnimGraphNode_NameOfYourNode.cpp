// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "AnimGraphNode_NameOfYourNode.h"

/////////////////////////////////////////////////////
// UAnimGraphNode_NameOfYourNode

UAnimGraphNode_NameOfYourNode::UAnimGraphNode_NameOfYourNode(const FPostConstructInitializeProperties& PCIP)
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

FString UAnimGraphNode_NameOfYourNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FString Result = *GetControllerDescription();
	Result += (TitleType == ENodeTitleType::ListView) ? TEXT("") : TEXT("\n");
	return Result;
}
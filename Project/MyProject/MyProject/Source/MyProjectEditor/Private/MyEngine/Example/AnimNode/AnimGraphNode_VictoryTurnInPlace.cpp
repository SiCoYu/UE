// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

//UE4 4.17 : error : Expected AnimGraphNode_VictoryTurnInPlace.h to be first header included.
//#include "MyProjectEditor.h"
#include "AnimGraphNode_VictoryTurnInPlace.h"
//#include "UtilStr.h"

/////////////////////////////////////////////////////
// UAnimGraphNode_VictoryTurnInPlace

UAnimGraphNode_VictoryTurnInPlace::UAnimGraphNode_VictoryTurnInPlace(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//Title Color!
FLinearColor UAnimGraphNode_VictoryTurnInPlace::GetNodeTitleColor() const
{
	return FLinearColor(0, 12, 12, 1);
}

//Node Category
FString UAnimGraphNode_VictoryTurnInPlace::GetNodeCategory() const
{
	return FString("Victory Anim Nodes");
}
FString UAnimGraphNode_VictoryTurnInPlace::GetControllerDescription() const
{
	return TEXT("~~~ Victory Turn In Place ~~~");
}

FText UAnimGraphNode_VictoryTurnInPlace::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	//FString Result = *GetControllerDescription();
	//Result += (TitleType == ENodeTitleType::ListView) ? TEXT("") : TEXT("\n");
	//return UtilStr::ConvFString2FText(Result);

	FString tmp = "Template";
	return FText::FromString(tmp);
}
// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "AnimInstanceCppSetVar.h"

//////////////////////////////////////////////////////////////////////////
// UYourAnimInstance

UAnimInstanceCppSetVar::UAnimInstanceCppSetVar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//set any default values for your variables here
	SkelControl_LeftUpperLegPos = FVector(0, 0, 0);
}
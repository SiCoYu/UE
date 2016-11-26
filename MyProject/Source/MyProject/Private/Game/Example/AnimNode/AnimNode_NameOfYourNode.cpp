// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "AnimNode_NameOfYourNode.h"

//#include "AnimationRuntime.h"

FAnimNode_NameOfYourNode::FAnimNode_NameOfYourNode()
	: FAnimNode_Base()
	, SampleFloat(128.333)
{
	WorldIsGame = false;
}

void FAnimNode_NameOfYourNode::Initialize(const FAnimationInitializeContext & Context)
{
	//Init the Inputs
	BasePose.Initialize(Context);
	OtherPose.Initialize(Context);

	//Get the Actor Owner
	OwningActor = Context.AnimInstance->GetSkelMeshComponent()->GetOwner();

	//Editor or Game?
	UWorld * TheWorld = Context.AnimInstance->GetWorld();
	if (!TheWorld) return;
	//~

	WorldIsGame = (TheWorld->WorldType == EWorldType::Game);
}

void FAnimNode_NameOfYourNode::CacheBones(const FAnimationCacheBonesContext & Context)
{
	BasePose.CacheBones(Context);
	OtherPose.CacheBones(Context);
}
void FAnimNode_NameOfYourNode::Update(const FAnimationUpdateContext & Context)
{
	//***************************************
	// Evaluate Graph, see AnimNode_Base, AnimNodeBase.h
	EvaluateGraphExposedInputs.Execute(Context);
	//***************************************

	//EDITOR
	//Editor mode? just use the base pose
	if (!WorldIsGame)
	{
		//if your node depends on 
		//actual actor instance, can't do anything in editor
	}

	//GAME
	//Actually in Game so the Owner Instance Should Exist
	else
	{
		//Try Again if not found
		if (!OwningActor) OwningActor =
			Context.AnimInstance->GetSkelMeshComponent()->GetOwner();

		//Not found
		if (!OwningActor)
		{
			UE_LOG(LogAnimation, Warning,
				TEXT("FAnimNode_NameOfYourNode::Update() Owning Actor was not found"));
			return;
			//~
		}

		//Do Stuff Based On Actor Owner
	}
	//~~

	// Do Updates 

	//Try To Update As Few of the Inputs As You Can

	//************************************************
	// FPoseLinkBase::Update Active Pose - this is what makes 
	//the glowing line thing happen and animations loop
	//***********************************************
	BasePose.Update(Context);



}

void FAnimNode_NameOfYourNode::Evaluate(FPoseContext & Output)
{
	// Return Base Pose, Un Modified 
	BasePose.Evaluate(Output);

	//Evaluate is returning the Output to this function,
	//which is returning the Output to the rest of the Anim Graph

	//In this case, we are passing the Output out variable into the BasePose

	//Basically saying, give us back the unmodified Base Pose

	//i.e, the bulk of your anim tree.
}
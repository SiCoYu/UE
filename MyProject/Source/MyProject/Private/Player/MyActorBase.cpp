#include "MyProject.h"
#include "MyActorBase.h"

AMyActorBase::AMyActorBase(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AMyActorBase::CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA)
{
	FConstraintInstance ConstraintInstance;

	//New Object
	UPhysicsConstraintComponent* ConstraintComp = NewObject<UPhysicsConstraintComponent>(RootSMA);
	if (!ConstraintComp)
	{
		return;
	}

	//Set Constraint Instance!
	ConstraintComp->ConstraintInstance = ConstraintInstance;

	//Set World Location
	ConstraintComp->SetWorldLocation(RootSMA->GetActorLocation());

	//Attach to Root!
	ConstraintComp->AttachToComponent(RootSMA->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform, NAME_None);

	//~~~ Init Constraint ~~~
	ConstraintComp->SetConstrainedComponents(RootSMA->GetStaticMeshComponent(), NAME_None, TargetSMA->GetStaticMeshComponent(), NAME_None);
}
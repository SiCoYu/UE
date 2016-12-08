#include "MyProject.h"
#include "PhysicsEngine/PhysicsConstraintActor.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "Engine/EngineTypes.h"
#include "DynamicCreateConstraintActor.h"

ADynamicCreateConstraintActor::ADynamicCreateConstraintActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void ADynamicCreateConstraintActor::CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA)
{
	//set up the constraint instance with all the desired values
	FConstraintInstance ConstraintInstance;

	//set values here, see functions I am sharing with you below
	//UYourStaticLibrary::SetLinearLimits(ConstraintInstance, ...); //or make the functions below non static
	//UYourStaticLibrary::SetAngularLimits(ConstraintInstance, ...);

	//New Object
	UPhysicsConstraintComponent* ConstraintComp = NewObject<UPhysicsConstraintComponent>(RootSMA);
	if (!ConstraintComp)
	{
		//UE_LOG constraint UObject could not be created!
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~
	//Set Constraint Instance!
	ConstraintComp->ConstraintInstance = ConstraintInstance;
	//~~~~~~~~~~~~~~~~~~~~~~~~

	//Set World Location
	ConstraintComp->SetWorldLocation(RootSMA->GetActorLocation());

	//Attach to Root!
	ConstraintComp->AttachTo(RootSMA->GetRootComponent(), NAME_None, EAttachLocation::KeepWorldPosition);

	//~~~ Init Constraint ~~~
	ConstraintComp->SetConstrainedComponents(RootSMA->StaticMeshComponent, NAME_None, TargetSMA->StaticMeshComponent, NAME_None);
}
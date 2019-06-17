#include "MyProject.h"
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

	// warning C4996: 'USceneComponent::AttachTo': This function is deprecated, please use AttachToComponent instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//Attach to Root!
	//ConstraintComp->AttachTo(RootSMA->GetRootComponent(), NAME_None, EAttachLocation::KeepWorldPosition);
	ConstraintComp->AttachToComponent(RootSMA->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform, NAME_None);

	//~~~ Init Constraint ~~~
	// warning C4996: 'AStaticMeshActor::StaticMeshComponent': StaticMeshComponent should not be accessed directly, please use GetStaticMeshComponent() function instead. StaticMeshComponent will soon be private and your code will not compile. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//ConstraintComp->SetConstrainedComponents(RootSMA->StaticMeshComponent, NAME_None, TargetSMA->StaticMeshComponent, NAME_None);
	ConstraintComp->SetConstrainedComponents(RootSMA->GetStaticMeshComponent(), NAME_None, TargetSMA->GetStaticMeshComponent(), NAME_None);
}
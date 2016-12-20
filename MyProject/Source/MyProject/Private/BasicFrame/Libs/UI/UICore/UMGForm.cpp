#include "MyProject.h"
#include "UMGForm.h"

UUMGForm::UUMGForm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUMGForm::OnSynchronizeProperties_Implementation()
{
	// Override this event in Blueprint
}

void UUMGForm::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}
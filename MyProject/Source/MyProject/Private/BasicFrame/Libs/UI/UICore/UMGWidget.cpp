#include "MyProject.h"
#include "UMGWidget.h"

//UUMGWidget::UUMGWidget(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//
//}

void UUMGWidget::OnSynchronizeProperties_Implementation()
{
	// Override this event in Blueprint
}

void UUMGWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}
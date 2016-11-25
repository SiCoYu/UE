#include "MyProject.h"
#include "ClearWidgetsPlayerController.h"

//AClearWidgetsPlayerController::AClearWidgetsPlayerController(const class FObjectInitializer& PCIP)
//	: Super(PCIP)
//{
//
//}

void AClearWidgetsPlayerController::ClearHUDWidgets_Implementation()
{
	/* Object Iterator for All User Widgets! */
	for (TObjectIterator<UUserWidget> Itr; Itr; ++Itr)
	{
		UUserWidget* LiveWidget = *Itr;

		/* If the Widget has no World, Ignore it (It's probably in the Content Browser!) */
		if (!LiveWidget->GetWorld())
		{
			continue;
		}
		else
		{
			LiveWidget->RemoveFromParent();
		}
	}
}
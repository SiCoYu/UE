#include "MyProject.h"
#include "ClearWidgetsPlayerController.h"
#include "ClearWidgetsGameMode.h"

//AClearWidgetsGameMode::AClearWidgetsGameMode(const class FObjectInitializer& PCIP)
//	: Super(PCIP)
//{
//
//}

// 客户端过地图
AClearWidgetsPlayerController* AClearWidgetsGameMode::ProcessClientTravel(FString& FURL, FGuid NextMapGuid, bool bSeamless, bool bAbsolute)
{
	// We call PreClientTravel directly on any local PlayerPawns (ie listen server)
	AClearWidgetsPlayerController* LocalPlayerController = NULL;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AClearWidgetsPlayerController* PlayerController = *Iterator;
		if (Cast<UNetConnection>(PlayerController->Player) != NULL)
		{
			/* Check if we're using our Custom Controller */
			AClearWidgetsPlayerController* MyController = Cast<AClearWidgetsPlayerController>(PlayerController);
			if (MyController)
			{
				MyController->ClearHUDWidgets();
			}

			// REMOTE PLAYER
			PlayerController->ClientTravel(FURL, TRAVEL_Relative, bSeamless, NextMapGuid);
		}
		else
		{
			// LOCAL PLAYER
			/* Check if we're using a GES Controller */
			AClearWidgetsPlayerController* MyController = Cast<AClearWidgetsPlayerController>(PlayerController);
			if (MyController)
			{
				MyController->ClearHUDWidgets();
			}

			LocalPlayerController = PlayerController;
			PlayerController->PreClientTravel(FURL, bAbsolute ? TRAVEL_Absolute : TRAVEL_Relative, bSeamless);
		}
	}
	return LocalPlayerController;
}
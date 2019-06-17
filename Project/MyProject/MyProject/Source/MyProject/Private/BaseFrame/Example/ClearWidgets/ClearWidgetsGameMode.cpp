#include "MyProject.h"
#include "ClearWidgetsPlayerController.h"
#include "ClearWidgetsGameMode.h"

//AClearWidgetsGameMode::AClearWidgetsGameMode(const class FObjectInitializer& PCIP)
//	: Super(PCIP)
//{
//
//}

// 客户端过地图
APlayerController* AClearWidgetsGameMode::ProcessClientTravel(FString& FURL, FGuid NextMapGuid, bool bSeamless, bool bAbsolute)
{
	// We call PreClientTravel directly on any local PlayerPawns (ie listen server)
	APlayerController* LocalPlayerController = NULL;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		// UE4 4.17 warning C4996: 'TAutoWeakObjectPtr<APlayerController>::operator T': Implicit conversion from TAutoWeakObjectPtr to the pointer type has been deprecated - use Get() instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//APlayerController* PlayerController = Iterator.get();
		// UE4.19.1 error C2440: 'initializing': cannot convert from 'const TWeakObjectPtr<APlayerController,FWeakObjectPtr>' to 'APlayerController *'
		//APlayerController* PlayerController = *Iterator;
		APlayerController* PlayerController = Cast<APlayerController>(Iterator->Get());

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
#include "MyProject.h"
#include "UmgInCpp.h"

UUmgInCpp::UUmgInCpp(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UUmgInCpp::showMenu()
{
	if (wMainMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyMainMenu = CreateWidget<UUserWidget>(this, wMainMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyMainMenu)
		{
			//let add it to the view port
			MyMainMenu->AddToViewport();
		}

		//Show the Cursor.
		//bShowMouseCursor = true;
	}
}
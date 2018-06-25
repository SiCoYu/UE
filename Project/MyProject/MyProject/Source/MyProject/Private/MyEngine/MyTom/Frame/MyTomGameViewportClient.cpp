#include "MyProject.h"
#include "MyTomGameViewportClient.h"

UMyTomGameViewportClient::UMyTomGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TOptional<bool> UMyTomGameViewportClient::QueryShowFocus(const EFocusCause InFocusCause) const
{
	// Consider your own special logic, you might want to call the super method first.
	return false;
}
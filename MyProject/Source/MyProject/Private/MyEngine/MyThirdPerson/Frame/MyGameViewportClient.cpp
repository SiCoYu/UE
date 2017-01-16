#include "MyProject.h"
#include "MyGameViewportClient.h"

UMyGameViewportClient::UMyGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TOptional<bool> UMyGameViewportClient::QueryShowFocus(const EFocusCause InFocusCause) const
{
	// Consider your own special logic, you might want to call the super method first.
	return false;
}
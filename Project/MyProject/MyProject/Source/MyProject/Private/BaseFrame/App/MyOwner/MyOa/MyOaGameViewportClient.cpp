#include "MyProject.h"
#include "MyOaGameViewportClient.h"

UMyOaGameViewportClient::UMyOaGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TOptional<bool> UMyOaGameViewportClient::QueryShowFocus(const EFocusCause InFocusCause) const
{
	// Consider your own special logic, you might want to call the super method first.
	return false;
}
#include "MyProject.h"
#include "MyViewportClient.h"

UMyViewportClient::UMyViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TOptional<bool> UMyViewportClient::QueryShowFocus(const EFocusCause InFocusCause) const
{
	// Consider your own special logic, you might want to call the super method first.
	return false;
}
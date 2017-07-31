#include "MyProject.h"
#include "MyGameViewportClientBase.h"

UMyGameViewportClientBase::UMyGameViewportClientBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TOptional<bool> UMyGameViewportClientBase::QueryShowFocus(const EFocusCause InFocusCause) const
{
	// Consider your own special logic, you might want to call the super method first.
	return false;
}
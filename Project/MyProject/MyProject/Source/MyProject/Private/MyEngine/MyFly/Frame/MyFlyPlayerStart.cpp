#include "MyProject.h"
#include "MyFlyPlayerStart.h"

AMyFlyPlayerStart::AMyFlyPlayerStart(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool AMyFlyPlayerStart::GetIsPlayerOnly()
{
	return true;
}
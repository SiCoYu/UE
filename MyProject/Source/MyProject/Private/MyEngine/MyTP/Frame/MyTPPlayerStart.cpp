#include "MyProject.h"
#include "MyTPPlayerStart.h"

AMyTPPlayerStart::AMyTPPlayerStart(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool AMyTPPlayerStart::GetIsPlayerOnly()
{
	return true;
}
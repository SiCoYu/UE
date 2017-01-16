#include "MyProject.h"
#include "MyPlayerStart.h"

AMyTPPlayerStart::AMyTPPlayerStart(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool AMyTPPlayerStart::GetIsPlayerOnly()
{
	return true;
}
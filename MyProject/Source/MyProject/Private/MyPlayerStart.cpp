#include "MyProject.h"
#include "MyPlayerStart.h"

AMyPlayerStart::AMyPlayerStart(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool AMyPlayerStart::GetIsPlayerOnly()
{
	return true;
}
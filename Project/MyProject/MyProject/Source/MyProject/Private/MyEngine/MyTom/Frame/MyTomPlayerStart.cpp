#include "MyProject.h"
#include "MyTomPlayerStart.h"

AMyTomPlayerStart::AMyTomPlayerStart(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool AMyTomPlayerStart::GetIsPlayerOnly()
{
	return true;
}
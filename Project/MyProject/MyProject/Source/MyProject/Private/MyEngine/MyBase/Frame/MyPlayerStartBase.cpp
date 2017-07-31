#include "MyProject.h"
#include "MyPlayerStartBase.h"

AMyPlayerStartBase::AMyPlayerStartBase(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool AMyPlayerStartBase::GetIsPlayerOnly()
{
	return true;
}
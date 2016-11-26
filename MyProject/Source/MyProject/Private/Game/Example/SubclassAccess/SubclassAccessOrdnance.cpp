#include "MyProject.h"
#include "SubclassAccessOrdnance.h"

ASubclassAccessOrdnance::ASubclassAccessOrdnance(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

float ASubclassAccessOrdnance::GetAmmoCost()
{
	return AmmoCost;
}
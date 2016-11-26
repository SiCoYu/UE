#include "MyProject.h"
#include "SubclassAccessOrdnance.h"
#include "SubclassAccessWeapon.h"

ASubclassAccessWeapon::ASubclassAccessWeapon(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void ASubclassAccessWeapon::HandleFiring()
{
	/* Check if we have Enough Ammo To Fire */
	float OrdnanceCost = WeaponConfig.OrdnanceClass->GetDefaultObject<ASubclassAccessOrdnance>()->GetAmmoCost();
	bool bEnoughAmmo = this->GetCurrentAmmo() >= OrdnanceCost;

	if (bEnoughAmmo)
	{
		this->FireWeapon(OrdnanceCost); // Tab-Out Pure-Virtual For Now!
	}
}

float ASubclassAccessWeapon::GetCurrentAmmo()
{
	return CurrentAmmoNum;
}

void ASubclassAccessWeapon::FireWeapon(float num)
{

}
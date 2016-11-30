#include "MyProject.h"
#include "TestUseEnum.h"

ATestUseEnum::ATestUseEnum(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

//YourClass.CPP
void ATestUseEnum::TestEnum(EVictoryEnum EnumValue)
{
	if (VictoryEnum == EVictoryEnum::VE_Dance)
	{
		VictoryEnum = EVictoryEnum::VE_Song;
	}
	else
	{
		VictoryEnum = EVictoryEnum::VE_Rain;
	}
}

FString ATestUseEnum::GetVictoryEnumAsString(EVictoryEnum EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EVictoryEnum"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetEnumName((int32)EnumValue); // for EnumValue == VE_Dance returns "VE_Dance"
}
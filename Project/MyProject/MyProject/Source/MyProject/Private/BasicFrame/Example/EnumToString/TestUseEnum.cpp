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

	// UE4 4.17 : warning C4996: 'UEnum::GetEnumName': GetEnumName is deprecated, call GetNameStringByIndex instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//return EnumPtr->GetEnumName((int32)EnumValue); // for EnumValue == VE_Dance returns "VE_Dance"
	return EnumPtr->GetNameStringByIndex((int32)EnumValue); // for EnumValue == VE_Dance returns "VE_Dance"
}
#include "MyProject.h"
#include "EnumToString.h"

DEFINE_LOG_CATEGORY(LogSomething);

void AYourClass::SomeFunction()
{
	EUsesEnum UseEnumValue = EUsesEnum::UseEnum_Good;
	UE_LOG(LogSomething, Log, TEXT("UseEnumValue as string : %s"), *GETENUMSTRING("EUsesEnum", UseEnumValue));
}
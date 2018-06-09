#include "MyProject.h"
#include "ClientScreenLogDevice.h"

MY_BEGIN_NAMESPACE(MyNS)

ClientScreenLogDevice::ClientScreenLogDevice()
{

}

void ClientScreenLogDevice::log(FString str, MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FLinearColor::Gray.ToRGBE(), TEXT("aaa"));
}

void ClientScreenLogDevice::warn(FString str, MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("aaa"));
}

void ClientScreenLogDevice::error(FString str, MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("aaa"));
}

MY_END_NAMESPACE
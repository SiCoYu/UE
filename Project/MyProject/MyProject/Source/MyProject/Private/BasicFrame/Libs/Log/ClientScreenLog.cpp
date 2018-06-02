#include "MyProject.h"
#include "ClientScreenLog.h"

MY_BEGIN_NAMESPACE(MyNS)

ClientScreenLog::ClientScreenLog()
{

}

void ClientScreenLog::log(FString str, MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FLinearColor::Gray.ToRGBE(), TEXT("aaa"));
}

void ClientScreenLog::warn(FString str, MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("aaa"));
}

void ClientScreenLog::error(FString str, MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("aaa"));
}

MY_END_NAMESPACE
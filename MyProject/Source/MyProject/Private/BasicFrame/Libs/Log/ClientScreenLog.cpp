#include "MyProject.h"
#include "ClientScreenLog.h"

ClientScreenLog::ClientScreenLog()
{

}

void ClientScreenLog::log(FString str, MLogType::MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FLinearColor::Gray.ToRGBE(), TEXT("aaa"));
}

void ClientScreenLog::warn(FString str, MLogType::MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("aaa"));
}

void ClientScreenLog::error(FString str, MLogType::MLogType type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("aaa"));
}
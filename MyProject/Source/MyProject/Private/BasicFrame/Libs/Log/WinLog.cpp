#include "MyProject.h"
#include "WinLog.h"

DEFINE_LOG_CATEGORY(ComLog);
DEFINE_LOG_CATEGORY(ComWarning);
DEFINE_LOG_CATEGORY(ComError);

WinLog::WinLog()
{

}

void WinLog::log(FString str, MLogType::MLogType type)
{
	//UE_LOG(YourLog, Log, TEXT(*str));
	UE_LOG(ComLog, Log, TEXT("aaa"));
}

void WinLog::warn(FString str, MLogType::MLogType type)
{
	UE_LOG(ComWarning, Log, TEXT("aaa"));
}

void WinLog::error(FString str, MLogType::MLogType type)
{
	UE_LOG(ComError, Log, TEXT("aaa"));
}
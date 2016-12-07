#include "MyProject.h"
#include "EditorWinLog.h"

DEFINE_LOG_CATEGORY(ComLog);
DEFINE_LOG_CATEGORY(ComWarning);
DEFINE_LOG_CATEGORY(ComError);

EditorWinLog::EditorWinLog()
{

}

void EditorWinLog::log(FString str, MLogType::MLogType type)
{
	//UE_LOG(YourLog, Log, TEXT(*str));
	UE_LOG(ComLog, Log, TEXT("aaa"));
}

void EditorWinLog::warn(FString str, MLogType::MLogType type)
{
	UE_LOG(ComWarning, Log, TEXT("aaa"));
}

void EditorWinLog::error(FString str, MLogType::MLogType type)
{
	UE_LOG(ComError, Log, TEXT("aaa"));
}
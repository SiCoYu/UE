#include "MyProject.h"
#include "EditorWinLog.h"

//DEFINE_LOG_CATEGORY(ComLog);
//DEFINE_LOG_CATEGORY(ComWarning);
//DEFINE_LOG_CATEGORY(ComError);

DEFINE_LOG_CATEGORY(MLogMacro_LogCategory);

EditorWinLog::EditorWinLog()
{

}

void EditorWinLog::log(FString str, MLogType type)
{
	//UE_LOG(YourLog, Log, str.GetCharArray().GetData());
	//UE_LOG(YourLog, Log, *str);
	//UE_LOG(YourLog, Log, TEXT(*str));
	//UE_LOG(ComLog, Log, TEXT("aaa"));
	MLogMacro_V_LOGM(ComLog, "aaa");
	MLogMacro_TRACE("aaa");
}

void EditorWinLog::warn(FString str, MLogType type)
{
	UE_LOG(ComWarning, Log, TEXT("aaa"));
	MLogMacro_V_LOGM(ComLog, "aaa");
	MLogMacro_TRACE("aaa");
}

void EditorWinLog::error(FString str, MLogType type)
{
	UE_LOG(ComError, Log, TEXT("aaa"));
	MLogMacro_V_LOGM(ComLog, "aaa");
	MLogMacro_TRACE("aaa");
}
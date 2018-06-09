#include "MyProject.h"
#include "NativeEditorWinLogDevice.h"

//DEFINE_LOG_CATEGORY(ComLog);
//DEFINE_LOG_CATEGORY(ComWarning);
//DEFINE_LOG_CATEGORY(ComError);

DEFINE_LOG_CATEGORY(MLogMacro_LogCategory);

NativeEditorWinLogDevice::NativeEditorWinLogDevice()
{

}

void NativeEditorWinLogDevice::log(FString str, MLogType type)
{
	//UE_LOG(YourLog, Log, str.GetCharArray().GetData());
	//UE_LOG(YourLog, Log, *str);
	//UE_LOG(YourLog, Log, TEXT(*str));
	//UE_LOG(ComLog, Log, TEXT("aaa"));
	MLogMacro_V_LOGM(ComLog, "aaa");
	MLogMacro_TRACE("aaa");
}

void NativeEditorWinLogDevice::warn(FString str, MLogType type)
{
	UE_LOG(ComWarning, Log, TEXT("aaa"));
	MLogMacro_V_LOGM(ComLog, "aaa");
	MLogMacro_TRACE("aaa");
}

void NativeEditorWinLogDevice::error(FString str, MLogType type)
{
	UE_LOG(ComError, Log, TEXT("aaa"));
	MLogMacro_V_LOGM(ComLog, "aaa");
	MLogMacro_TRACE("aaa");
}
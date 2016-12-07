#include "MyProject.h"
#include "ClientWinLog.h"

ClientWinLog::ClientWinLog()
{

}

void ClientWinLog::log(FString str, MLogType::MLogType type)
{
	mPlayerController->ClientMessage("aaa");
}

void ClientWinLog::warn(FString str, MLogType::MLogType type)
{
	mPlayerController->ClientMessage("aaa");
}

void ClientWinLog::error(FString str, MLogType::MLogType type)
{
	mPlayerController->ClientMessage("aaa");
}
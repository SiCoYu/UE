#include "MyProject.h"
#include "ClientWinLog.h"

MY_BEGIN_NAMESPACE(MyNS)

ClientWinLog::ClientWinLog()
{

}

void ClientWinLog::log(FString str, MLogType::MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

void ClientWinLog::warn(FString str, MLogType::MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

void ClientWinLog::error(FString str, MLogType::MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

MY_END_NAMESPACE
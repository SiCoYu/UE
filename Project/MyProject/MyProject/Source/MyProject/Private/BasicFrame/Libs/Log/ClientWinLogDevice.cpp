#include "MyProject.h"
#include "ClientWinLogDevice.h"

MY_BEGIN_NAMESPACE(MyNS)

ClientWinLog::ClientWinLog()
{

}

void ClientWinLog::log(FString str, MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

void ClientWinLog::warn(FString str, MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

void ClientWinLog::error(FString str, MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

MY_END_NAMESPACE
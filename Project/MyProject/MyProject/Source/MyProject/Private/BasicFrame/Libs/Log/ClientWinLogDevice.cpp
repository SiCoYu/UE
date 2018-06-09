#include "MyProject.h"
#include "ClientWinLogDevice.h"

MY_BEGIN_NAMESPACE(MyNS)

ClientWinLogDevice::ClientWinLogDevice()
{

}

void ClientWinLogDevice::log(FString str, MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

void ClientWinLogDevice::warn(FString str, MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

void ClientWinLogDevice::error(FString str, MLogType type)
{
	this->mPlayerController->ClientMessage("aaa");
}

MY_END_NAMESPACE
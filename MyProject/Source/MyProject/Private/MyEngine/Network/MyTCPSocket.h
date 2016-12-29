#pragma once

#include "Engine/EngineTypes.h"	// FTimerHandle
#include "Networking.h"	// 网络一次性全包括，防止只包含部分导致编译不过
//#include "Common/TcpSocketBuilder.h"
//#include "Interfaces/IPv4/IPv4Endpoint.h"	// 只包含 IPv4Endpoint.h 会编译不过 // FIPv4Endpoint
//#include "Sockets.h"
#include "Containers/UnrealString.h"
#include "UObject/Object.h"

/**
 * @brief https://wiki.unrealengine.com/TCP_Socket_Listener,_Receive_Binary_Data_From_an_IP/Port_Into_UE4,_(Full_Code_Sample)
 */

// FTimerDelegate::CreateUObject 绑定必须继承 UObject
// error C2243: 'type cast': conversion from 'MyTCPSocket *' to 'const UObjectBase *' exists, but is inaccessible
//class MyTCPSocket : UObject
class MyTCPSocket : public UObject
{
public:
	// Engine\Plugins\Online\OnlineFramework\Source\Lobby\Private\LobbyBeaconState.cpp
	FTimerHandle OneSecTimerHandle;
	FTimerHandle CancelRPCFailsafe;

	FSocket* ListenerSocket;
	FSocket* ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;

	bool StartTCPReceiver(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
		);

	FSocket* CreateTCPConnectionListener(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort,
		const int32 ReceiveBufferSize = 2 * 1024 * 1024
		);

	//Timer functions, could be threads
	void TCPConnectionListener(); 	//can thread this eventually
	void TCPSocketListener();		//can thread this eventually


									//Format String IP4 to number array
	bool FormatIP4ToNumber(const FString& TheIP, uint8(&Out)[4]);

	//Rama's StringFromBinaryArray
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);

	void Launch();

	// https://wiki.unrealengine.com/Third_Party_Socket_Server_Connection
public:
	FSocket* ClientSocket;
	void ConnectThirdPartySocketServer();
	void SendThirdPartyData();
};
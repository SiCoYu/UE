#pragma once

#include "SChatMsg.h"
#include "MyPlayerState.generated.h"

UCLASS()
class AMyPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()


	// Begin APlayerState interface
	/** clear scores */
	virtual void Reset() override;

	/**
	 * Set the team 
	 *
	 * @param	InController	The controller to initialize state with
	 */
	virtual void ClientInitialize(class AController* InController) override;

	virtual void UnregisterPlayerWithSession() override;

	virtual void CopyProperties(class APlayerState* PlayerState) override;

	// https://wiki.unrealengine.com/Slate,_Simple_C%2B%2B_Chat_System
public:
	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
	virtual void UserChatRPC(const FSChatMsg& newmessage); // first rpc for the server
	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
		virtual void UserChat(const FSChatMsg& newmessage); // second rpc for all the clients
};

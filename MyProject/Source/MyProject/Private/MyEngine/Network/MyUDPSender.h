#pragma once

//Networking
#include "Networking.h"

//Base
#include "MyUDPSender.generated.h"

/**
 * @brief https://wiki.unrealengine.com/UDP_Socket_Sender_Receiver_From_One_UE4_Instance_To_Another
 */

UCLASS()
class AMyUDPSender : public AActor
{
	GENERATED_UCLASS_BODY()

	bool IsUDP;

	//UFUNCTION(BlueprintCallable, Category=RamaUDPSender)
	bool RamaUDPSender_SendString(FString ToSend);

public:
	TSharedPtr<FInternetAddr>	RemoteAddr;
	FSocket* SenderSocket;

	bool StartUDPSender(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort,
		bool UDP = false
		);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rama UDP Sender")
		bool ShowOnScreenDebugMessages;


	//ScreenMsg
	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}


public:

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
#pragma once

// TODO:
#include "HAL/Platform.h"	// int32
//#include "GenericPlatform/GenericPlatform.h"	// int32
#include "Internationalization/Text.h"	// FText
#include "Input/Events.h"	// FKeyEvent
#include "SChatMsg.generated.h"

/**
 * @url https://wiki.unrealengine.com/Slate,_Simple_C%2B%2B_Chat_System
 */

USTRUCT()
struct FSChatMsg // Struct to hold the message data to be passed between classes
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() // UProperty means this variable will be replicated
	int32 Type;

	UPROPERTY()
	FText Username;

	UPROPERTY()
	FText Text;

	FText Timestamp; // Dont replicate time because we can set it locally once we receive the struct

	double Created;

	void Init(int32 NewType, FText NewUsername, FText NewText) // Assign only the vars we wish to replicate
	{
		Type = NewType;
		Username = NewUsername;
		Text = NewText;
	}

	void SetTime(FText NewTimestamp, double NewCreated)
	{
		Timestamp = NewTimestamp;
		Created = NewCreated;
	}

	void Destroy()
	{
		Type = NULL;
		Username.GetEmpty();
		Text.GetEmpty();
		Timestamp.GetEmpty();
		Created = NULL;
	}
};
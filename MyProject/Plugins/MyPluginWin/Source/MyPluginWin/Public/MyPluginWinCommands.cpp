// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyPluginWinPrivatePCH.h"
#include "MyPluginWinCommands.h"

#define LOCTEXT_NAMESPACE "FMyPluginWinModule"

void FMyPluginWinCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MyPluginWin", "Bring up MyPluginWin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "ExportPakPrivatePCH.h"
#include "ExportPakCommands.h"

#define LOCTEXT_NAMESPACE "FExportPakModule"

void FExportPakCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ExportPak", "Bring up ExportPak window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

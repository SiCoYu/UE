// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "MyExportAssetDependecies.h"
#include "MyExportAssetDependeciesCommands.h"

#define LOCTEXT_NAMESPACE "FMyExportAssetDependeciesModule"

void FMyExportAssetDependeciesCommands::RegisterCommands()
{
    UI_COMMAND(PluginAction, "ExportAssetDependecies", "Execute ExportAssetDependecies action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
// error : Expected MyExportAssetDependeciesCommands.h to be first header included.
#include "MyExportAssetDependeciesCommands.h"
#include "MyExportAssetDependecies.h"

#define LOCTEXT_NAMESPACE "FMyExportAssetDependeciesModule"

void FMyExportAssetDependeciesCommands::RegisterCommands()
{
    UI_COMMAND(PluginAction, "ExportAssetDependecies", "Execute ExportAssetDependecies action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

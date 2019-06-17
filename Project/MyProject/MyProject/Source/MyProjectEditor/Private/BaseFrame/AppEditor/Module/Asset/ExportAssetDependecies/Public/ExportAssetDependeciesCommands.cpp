// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "ExportAssetDependeciesPrivatePCH.h"
//#include "ExportAssetDependecies.h"
#include "ExportAssetDependeciesCommands.h"

#define LOCTEXT_NAMESPACE "FExportAssetDependeciesModule"

void FExportAssetDependeciesCommands::RegisterCommands()
{
    UI_COMMAND(PluginAction, "ExportAssetDependecies", "Execute ExportAssetDependecies action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "MyExportAssetDependeciesStyle.h"

class FMyExportAssetDependeciesCommands : public TCommands<FMyExportAssetDependeciesCommands>
{
public:

    FMyExportAssetDependeciesCommands()
        : TCommands<FMyExportAssetDependeciesCommands>(TEXT("ExportAssetDependecies"), NSLOCTEXT("Contexts", "ExportAssetDependecies", "ExportAssetDependecies Plugin"), NAME_None, FMyExportAssetDependeciesStyle::GetStyleSetName())
    {
    }

    // TCommands<> interface
    virtual void RegisterCommands() override;

public:
    TSharedPtr< FUICommandInfo > PluginAction;
};
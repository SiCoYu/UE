// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
// error : Expected MyExportAssetDependeciesSettings.h to be first header included.
#include "ExportAssetDependeciesSettings.h"
#include "MyExportAssetDependecies.h"
#include "UObject/ConstructorHelpers.h"

#define LOCTEXT_NAMESPACE "MyExportAssetDependecies"

UMyExportAssetDependeciesSettings::UMyExportAssetDependeciesSettings(const FObjectInitializer& Initializer)
    : Super(Initializer)
{

}

#undef LOCTEXT_NAMESPACE

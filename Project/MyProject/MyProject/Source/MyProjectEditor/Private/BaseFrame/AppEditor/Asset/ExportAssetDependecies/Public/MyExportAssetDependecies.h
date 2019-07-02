// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;
class UMyExportAssetDependeciesSettings;
class FAssetRegistryModule;
struct FMyDependicesInfo;

DECLARE_LOG_CATEGORY_EXTERN(MyLogExportAssetDependecies, Log, All);

class FMyExportAssetDependeciesModule/* : public IModuleInterface*/
{
public:

    /** IModuleInterface implementation */
    //virtual void StartupModule() override;
    //virtual void ShutdownModule() override;
	void StartupModule();
	void ShutdownModule();

    /** This function will be bound to Command. */
    void PluginButtonClicked();
	void ExportAssetDependecies();

private:

    void AddToolbarExtension(FToolBarBuilder& Builder);
    void AddMenuExtension(FMenuBuilder& Builder);

    void GatherDependenciesInfoRecursively(FAssetRegistryModule &AssetRegistryModule, const FString &TargetLongPackageName,
        TArray<FString> &DependicesInGameContentDir, TArray<FString> &OtherDependices);

    /** This will save the dependencies information to the OutputPath/AssetDependencies.json */
    void SaveDependicesInfo(const TMap<FString, FMyDependicesInfo> &DependicesInfos);

private:
    TSharedPtr<class FUICommandList> PluginCommands;
};
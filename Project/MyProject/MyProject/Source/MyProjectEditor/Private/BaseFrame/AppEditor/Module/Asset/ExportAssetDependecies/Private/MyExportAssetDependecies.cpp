// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "MyExportAssetDependecies.h"
#include "MyExportAssetDependeciesStyle.h"
#include "MyExportAssetDependeciesCommands.h"

#include "MyExportAssetDependeciesSettings.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

#include "LevelEditor.h"

#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#include "AssetRegistryModule.h"
#include "ARFilter.h"
#include "ModuleManager.h"
#include "ISettingsModule.h"
#include "PlatformFile.h"
#include "PlatformFilemanager.h"
#include "FileHelper.h"
#include "json.h"

DEFINE_LOG_CATEGORY(MyLogExportAssetDependecies);


static const FName MyExportAssetDependeciesTabName("ExportAssetDependecies");

#define LOCTEXT_NAMESPACE "FMyExportAssetDependeciesModule"

void FMyExportAssetDependeciesModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    FMyExportAssetDependeciesStyle::Initialize();
    FMyExportAssetDependeciesStyle::ReloadTextures();

    FMyExportAssetDependeciesCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    PluginCommands->MapAction(
        FMyExportAssetDependeciesCommands::Get().PluginAction,
        FExecuteAction::CreateRaw(this, &MyFExportAssetDependeciesModule::PluginButtonClicked),
        FCanExecuteAction());

    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

    {
        TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
        MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyExportAssetDependeciesModule::AddMenuExtension));

        LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
    }

    {
        TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
        ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMyExportAssetDependeciesModule::AddToolbarExtension));

        LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
    }

    // Initialize setting, take care of this registry syntax
    {
        ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
        if (SettingsModule != nullptr)
        {
            // ClassViewer Editor Settings
            SettingsModule->RegisterSettings("Project", "Game", "MyExportAssetDependencies",
                LOCTEXT("MyExportAssetDependenciesSettingsName", "Export Asset Dependencies"),
                LOCTEXT("MyExportAssetDependenciesSettingsDescription", "Export Asset Dependencies."),
                GetMutableDefault<UMyExportAssetDependeciesSettings>()
            );
        }
    }
}

void FMyExportAssetDependeciesModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.
    FMyExportAssetDependeciesStyle::Shutdown();

    FMyExportAssetDependeciesCommands::Unregister();
}

void FExportAssetDependeciesModule::PluginButtonClicked()
{
    // TODO
    // Should check whether the game content is dirty.

    // If loading assets
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
    if (AssetRegistryModule.Get().IsLoadingAssets())
    {
        // We are still discovering assets, listen for the completion delegate before building the graph
        if (!AssetRegistryModule.Get().OnFilesLoaded().IsBoundToObject(this))
        {
            AssetRegistryModule.Get().OnFilesLoaded().AddRaw(this, &FMyExportAssetDependeciesModule::ExportAssetDependecies);
        }
    }
    else
    {
        ExportAssetDependecies();
    }
}


void FMyExportAssetDependeciesModule::AddMenuExtension(FMenuBuilder& Builder)
{
    Builder.AddMenuEntry(FMyExportAssetDependeciesCommands::Get().PluginAction);
}

struct FMyDependicesInfo
{
    TArray<FString> DependicesInGameContentDir;
    TArray<FString> OtherDependices;
    FString AssetClassString;
};

void FMyExportAssetDependeciesModule::ExportAssetDependecies()
{
    // Validate settings
    auto CurrentSettings = GetMutableDefault<UMyExportAssetDependeciesSettings>();
    if (!CurrentSettings)
    {
        UE_LOG(LogExportAssetDependecies, Error, TEXT("Cannot read ExportAssetDependeciesSettings"));
        return;
    }

    // TODO
    // 1.Check input paths validation
    // 2.Check it has valid package path.
    if (CurrentSettings->PackagesToExport.Num() == 0)
    {
        ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
        if (SettingsModule != nullptr)
        {
            // If there is no PackagesToExport set, just to the setting viewer.
            SettingsModule->ShowViewer("Project", "Game", "ExportAssetDependencies");

            // UE4 API to show an editor notification.
            auto Message = LOCTEXT("MyExportAssetDependeciesNoValidTargetPackages", "No valid target packages set.");
            FNotificationInfo Info(Message);
            Info.bUseSuccessFailIcons = true;
            FSlateNotificationManager::Get().AddNotification(Info)->SetCompletionState(SNotificationItem::CS_Fail);

            UE_LOG(LogExportAssetDependecies, Log, TEXT("No valid target packages set."));
            return;
        }
    }

    TMap<FString, FMyDependicesInfo> DependicesInfos;
    for (auto &PackageFilePath : CurrentSettings->PackagesToExport)
    {
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

		// UE_DEPRECATED(4.18, "FStringAssetReference was renamed to FSoftObjectPath as it is now not always a string and can also refer to a subobject")
		// Engine\Source\Runtime\CoreUObject\Public\UObject\SoftObjectPath.h
        //FStringAssetReference AssetRef = PackageFilePath.FilePath;
		FSoftObjectPath AssetRef = PackageFilePath.FilePath;
        FString TargetLongPackageName = AssetRef.GetLongPackageName();


        if (FPackageName::DoesPackageExist(TargetLongPackageName))
        {
            auto &DependicesInfoEntry = DependicesInfos.Add(TargetLongPackageName);

            // Try get asset type.
            {
                TArray<FAssetData> AssetDataList;
                bool  bResult = AssetRegistryModule.Get().GetAssetsByPackageName(FName(*TargetLongPackageName), AssetDataList);
                if (!bResult || AssetDataList.Num() == 0)
                {
                    UE_LOG(LogExportAssetDependecies, Error, TEXT("Failed to get AssetData of  %s, please check."), *TargetLongPackageName);
                    return;
                }

                if (AssetDataList.Num() > 1)
                {
                    UE_LOG(MyLogExportAssetDependecies, Error, TEXT("Got multiple AssetData of  %s, please check."), *TargetLongPackageName);
                }

                DependicesInfoEntry.AssetClassString = AssetDataList[0].AssetClass.ToString();
            }

            GatherDependenciesInfoRecursively(AssetRegistryModule, TargetLongPackageName, DependicesInfoEntry.DependicesInGameContentDir, DependicesInfoEntry.OtherDependices);
        }

        TArray<FName>  ACs;
        AssetRegistryModule.Get().GetAncestorClassNames(*TargetLongPackageName, ACs);
    }

    // Write Results
    SaveDependicesInfo(DependicesInfos);
}

void FMyExportAssetDependeciesModule::GatherDependenciesInfoRecursively(FAssetRegistryModule &AssetRegistryModule,
    const FString &TargetLongPackageName,
    TArray<FString> &DependicesInGameContentDir,
    TArray<FString> &OtherDependices)
{
    TArray<FName> Dependencies;
    bool bGetDependenciesSuccess = AssetRegistryModule.Get().GetDependencies(FName(*TargetLongPackageName), Dependencies, EAssetRegistryDependencyType::Packages);
    if (bGetDependenciesSuccess)
    {
        for (auto &d : Dependencies)
        {
            // Pick out packages in game content dir.
            FString LongDependentPackageName = d.ToString();
            if (LongDependentPackageName.StartsWith("/Game"))
            {
                // Try find firstly to avoid duplicated entry.
                if (DependicesInGameContentDir.Find(LongDependentPackageName) == INDEX_NONE)
                {
                    DependicesInGameContentDir.Add(LongDependentPackageName);
                    GatherDependenciesInfoRecursively(AssetRegistryModule, LongDependentPackageName, DependicesInGameContentDir, OtherDependices);
                }
            }
            else
            {
                if (OtherDependices.Find(LongDependentPackageName) == INDEX_NONE)
                {
                    OtherDependices.Add(LongDependentPackageName);
                    GatherDependenciesInfoRecursively(AssetRegistryModule, LongDependentPackageName, DependicesInGameContentDir, OtherDependices);
                }
            }
        }
    }
}

void FMyExportAssetDependeciesModule::SaveDependicesInfo(const TMap<FString, FDependicesInfo> &DependicesInfos)
{
    TSharedPtr<FJsonObject> RootJsonObject = MakeShareable(new FJsonObject);
    for (auto &DependicesInfoEntry : DependicesInfos)
    {
        TSharedPtr<FJsonObject> EntryJsonObject = MakeShareable(new FJsonObject);

        // Write current AssetClass.
        EntryJsonObject->SetStringField("AssetClass", DependicesInfoEntry.Value.AssetClassString);

        // Write dependencies in game content dir.
        {
            TArray< TSharedPtr<FJsonValue> > DependenciesEntry;
            for (auto &d : DependicesInfoEntry.Value.DependicesInGameContentDir)
            {
                DependenciesEntry.Add(MakeShareable(new FJsonValueString(d)));
            }
            EntryJsonObject->SetArrayField("DependenciesInGameContentDir", DependenciesEntry);
        }

        // Write dependencies not in game content dir.
        {
            TArray< TSharedPtr<FJsonValue> > DependenciesEntry;
            for (auto &d : DependicesInfoEntry.Value.OtherDependices)
            {
                DependenciesEntry.Add(MakeShareable(new FJsonValueString(d)));
            }
            EntryJsonObject->SetArrayField("OtherDependencies", DependenciesEntry);
        }

        RootJsonObject->SetObjectField(DependicesInfoEntry.Key, EntryJsonObject);
    }

    FString OutputString;
    auto JsonWirter = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(RootJsonObject.ToSharedRef(), JsonWirter);

	// UE$ 4.22 warning C4996: 'FPaths::GameSavedDir': FPaths::GameSavedDir() has been superseded by FPaths::ProjectSavedDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
    //FString ResultFileFilename = FPaths::Combine(FPaths::GameSavedDir(), TEXT("ExportAssetDependecies"), TEXT("/AssetDependencies.json"));
	FString ResultFileFilename = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("ExportAssetDependecies"), TEXT("/AssetDependencies.json"));
    ResultFileFilename = FPaths::ConvertRelativePathToFull(ResultFileFilename);

    // Attention to FFileHelper::EEncodingOptions::ForceUTF8 here. 
    // In some case, UE4 will save as UTF16 according to the content.
    bool bSaveSuccess = FFileHelper::SaveStringToFile(OutputString, *ResultFileFilename, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    if (bSaveSuccess)
    {
        // UE4 API to show an editor notification.
        auto Message = LOCTEXT("ExportAssetDependeciesSuccessNotification", "Succeed to export asset dependecies.");
        FNotificationInfo Info(Message);
        Info.bFireAndForget = true;
        Info.ExpireDuration = 5.0f;
        Info.bUseSuccessFailIcons = false;
        Info.bUseLargeFont = false;

        const FString HyperLinkText = ResultFileFilename;
        Info.Hyperlink = FSimpleDelegate::CreateStatic([](FString SourceFilePath)
        {
            FPlatformProcess::ExploreFolder(*SourceFilePath);
        }, HyperLinkText);
        Info.HyperlinkText = FText::FromString(HyperLinkText);

        FSlateNotificationManager::Get().AddNotification(Info)->SetCompletionState(SNotificationItem::CS_Success);

        UE_LOG(MyLogExportAssetDependecies, Log, TEXT("%s. At %s"), *Message.ToString(), *ResultFileFilename);
    }
    else
    {
        UE_LOG(MyLogExportAssetDependecies, Error, TEXT("Failed to export %s"), *ResultFileFilename);
    }
}

void FMyExportAssetDependeciesModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
    Builder.AddToolBarButton(FMyExportAssetDependeciesCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyExportAssetDependeciesModule, MyExportAssetDependecies)
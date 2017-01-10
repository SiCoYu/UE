// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyPluginWinPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "MyPluginWinStyle.h"
#include "MyPluginWinCommands.h"

#include "LevelEditor.h"

static const FName MyPluginWinTabName("MyPluginWin");

#define LOCTEXT_NAMESPACE "FMyPluginWinModule"

void FMyPluginWinModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMyPluginWinStyle::Initialize();
	FMyPluginWinStyle::ReloadTextures();

	FMyPluginWinCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMyPluginWinCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMyPluginWinModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyPluginWinModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMyPluginWinModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyPluginWinTabName, FOnSpawnTab::CreateRaw(this, &FMyPluginWinModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMyPluginWinTabTitle", "MyPluginWin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMyPluginWinModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMyPluginWinStyle::Shutdown();

	FMyPluginWinCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MyPluginWinTabName);
}

TSharedRef<SDockTab> FMyPluginWinModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMyPluginWinModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MyPluginWin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FMyPluginWinModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(MyPluginWinTabName);
}

void FMyPluginWinModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMyPluginWinCommands::Get().OpenPluginWindow);
}

void FMyPluginWinModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMyPluginWinCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPluginWinModule, MyPluginWin)
// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "IProjectManager.h"
#include "Features/IModularFeatures.h"
#include "UniquePtr.h"
#include "ProjectDescriptor.h"

DEFINE_LOG_CATEGORY(MyScriptGeneratorPlugin);

class FMyScriptGeneratorPlugin : public IScriptGeneratorPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** IScriptGeneratorPlugin interface */
	virtual FString GetGeneratedCodeModuleName() const override { return TEXT("MyScriptGeneratorPlugin"); }
	virtual bool ShouldExportClassesForModule(const FString& ModuleName, EBuildModuleType::Type ModuleType, const FString& ModuleGeneratedIncludeDirectory) const override;
	virtual bool SupportsTarget(const FString& TargetName) const override;
	virtual void Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory, const FString& IncludeBase) override;
	virtual void ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename, bool bHasChanged) override;
	virtual void FinishExport() override;
	virtual FString GetGeneratorName() const override;
};

IMPLEMENT_MODULE(FMyScriptGeneratorPlugin, MyScriptGeneratorPlugin)


void FMyScriptGeneratorPlugin::StartupModule()
{
	// Register ourselves as an editor feature
	IModularFeatures::Get().RegisterModularFeature(TEXT("ScriptGenerator"), this);
}

void FMyScriptGeneratorPlugin::ShutdownModule()
{
	// Unregister our feature
	IModularFeatures::Get().UnregisterModularFeature(TEXT("ScriptGenerator"), this);
}

FString FMyScriptGeneratorPlugin::GetGeneratorName() const
{
	
}

void FScriptGeneratorPlugin::Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory, const FString& IncludeBase)
{
	UE_LOG(LogScriptGenerator, Log, TEXT("Output directory: %s"), *OutputDirectory);
}

bool FMyScriptGeneratorPlugin::ShouldExportClassesForModule(const FString& ModuleName, EBuildModuleType::Type ModuleType, const FString& ModuleGeneratedIncludeDirectory) const
{ 
	bool bCanExport = (ModuleType == EBuildModuleType::EngineRuntime || ModuleType == EBuildModuleType::GameRuntime);
	if (bCanExport)
	{
		// Only export functions from selected modules
		static struct FSupportedModules
		{
			TArray<FString> SupportedScriptModules;
			FSupportedModules()
			{
				GConfig->GetArray(TEXT("Plugins"), TEXT("ScriptSupportedModules"), SupportedScriptModules, GEngineIni);
			}
		} SupportedModules;
		bCanExport = SupportedModules.SupportedScriptModules.Num() == 0 || SupportedModules.SupportedScriptModules.Contains(ModuleName);
	}
	return bCanExport;
}

void FMyScriptGeneratorPlugin::ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename, bool bHasChanged)
{
	
}

void FMyScriptGeneratorPlugin::FinishExport()
{
	
}

bool FMyScriptGeneratorPlugin::SupportsTarget(const FString& TargetName) const
{
	// We only support the target if it explicitly enables the required script plugin in its uproject file
	bool bSupportsTarget = false;
	if (FPaths::IsProjectFilePathSet())
	{
		FProjectDescriptor ProjectDescriptor;
		FText OutError;
		if (ProjectDescriptor.Load(FPaths::GetProjectFilePath(), OutError))
		{
			for (auto& PluginDescriptor : ProjectDescriptor.Plugins)
			{
				// For your own script plugin you might want to change the hardcoded name here to something else
				if (PluginDescriptor.bEnabled && PluginDescriptor.Name == TEXT("MyScriptGeneratorPlugin"))
				{
					bSupportsTarget = true;
					break;
				}
			}
		}
	}
	return bSupportsTarget;
}
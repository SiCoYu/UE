// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExportAssetDependecies : ModuleRules
{
	//public ExportAssetDependecies(TargetInfo Target)
	public ExportAssetDependecies(ReadOnlyTargetRules Target) : base(Target)
	{
		// UE4 4.22  warning : Modules must specify an explicit precompiled header (eg. PrivatePCHHeaderFile = "Public/ExportAssetDependecies.h") from UE 4.21 onwards.
		this.PrivatePCHHeaderFile = "Public/ExportAssetDependeciesPrivatePCH.h";

		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.

		PublicIncludePaths.AddRange(
			new string[] {
				"ExportAssetDependecies/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"ExportAssetDependecies/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Json",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}

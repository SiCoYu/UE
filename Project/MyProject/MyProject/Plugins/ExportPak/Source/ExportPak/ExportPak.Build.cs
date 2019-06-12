// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExportPak : ModuleRules
{
	public ExportPak(ReadOnlyTargetRules Target) : base(Target)
	{
		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
		this.PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;;

		// UE4 4.22 warning : Modules must specify an explicit precompiled header (eg. PrivatePCHHeaderFile = "Private/MyPluginPrivatePCH.h") from UE 4.21 onwards.

		PublicIncludePaths.AddRange(
			new string[] {
				"ExportPak/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"ExportPak/Private",
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
                "EditorStyle",
                "PropertyEditor",
				"Json",
                "UATHelper",
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

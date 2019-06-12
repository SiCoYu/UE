// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyPluginWin : ModuleRules
{
	//public MyPluginWin(TargetInfo Target)
	public MyPluginWin(ReadOnlyTargetRules Target) : base(Target)
    {
		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
		//this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// UE4 4.22 warning : Modules must specify an explicit precompiled header (eg. PrivatePCHHeaderFile = "Private/MyPluginPrivatePCH.h") from UE 4.21 onwards.
		this.PrivatePCHHeaderFile = "Private/MyPluginWinPrivatePCH.h";

		PublicIncludePaths.AddRange(
			new string[] {
				"MyPluginWin/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"MyPluginWin/Private",
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

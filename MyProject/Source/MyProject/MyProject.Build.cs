// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject : ModuleRules
{
	public MyProject(TargetInfo Target)
	{
        PrivateIncludePaths.AddRange(
            new string[] {
                "MyProject/Private/Game/DataStruct",
                "MyProject/Private/Game/EngineWrap",
                "MyProject/Private/Game/FrameWork",
                "MyProject/Private/Game/Socket",

                "MyProject/Private/UI/Widgets",
                "MyProject/Private/Game/UI/UICore",
                "MyProject/Private/Game/UI/UIInterActive/UIPack",
	        }
        );

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
				"Slate",
				"SlateCore",
                "UMG",
			}
        );

        //MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
		
		
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ThirdPartyPath, "v8", "include"),
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"Coupling/Private",
				// ... add other private include paths required here ...
				Path.Combine(ThirdPartyPath, "v8", "include"),
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
		
		LoadV8(Target);
		}
	}
	
	/// <summary>
	/// Accessor for the Module's path
	/// </summary>
	protected string ModulePath
	{
		get 
		{ 
			return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
		}
	}
	
	/// <summary>
	/// Accessor for thee ThirdParty Path.
	/// </summary>
	protected string ThirdPartyPath
	{
		get 
		{ 
			return Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "ThirdParty"));
		}
	}

	private bool LoadV8(TargetInfo Target)
	{
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			string PlatformString;
			string LibrariesPath = Path.Combine(ThirdPartyPath, "v8", "lib");

			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				PlatformString = "x64";
				LibrariesPath = Path.Combine(LibrariesPath, "Win64");
			}
			else
			{
				PlatformString = "ia32";
				LibrariesPath = Path.Combine(LibrariesPath, "Win32");
			}

			LibrariesPath = Path.Combine(LibrariesPath, "Debug");

			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icui18n.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icuuc.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_base.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_libbase.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_nosnapshot.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_snapshot.lib"));

			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "v8", "Includes"));

			Definitions.Add(string.Format("WITH_COUPLING=1"));

			return true;
		}

		Definitions.Add(string.Format("WITH_COUPLING=0"));
		return false;
	}
}

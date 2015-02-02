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
	}
}

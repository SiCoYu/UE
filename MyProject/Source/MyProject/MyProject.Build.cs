// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MyProject : ModuleRules
{
	public MyProject(TargetInfo Target)
	{
        PrivateIncludePaths.AddRange(
            new string[] {
                // Libs 区域
                "MyProject/Private/Game/Libs/Common",
                "MyProject/Private/Game/Libs/DataStruct",
                "MyProject/Private/Game/Libs/EngineWrap",
                "MyProject/Private/Game/Libs/FrameWork",
                "MyProject/Private/Game/Libs/NetWork/Socket",
                "MyProject/Private/Game/Libs/NetWork/Cmd",

                "MyProject/Private/Game/Libs/UI/UICore",
                "MyProject/Private/Game/Libs/Log",
                "MyProject/Private/Game/Libs/Table",
                "MyProject/Private/Game/Libs/Table/ItemObject",
                "MyProject/Private/Game/Libs/Util",
                "MyProject/Private/Game/Libs/Resource/LoadItem",

                "MyProject/Private/Game/Libs/LuaCBridge",
                "MyProject/Private/Game/Libs/Thread",
                "MyProject/Private/Game/Libs/FastDelegate",
                "MyProject/Private/Game/Libs/Tools",
                "MyProject/Private/Game/Libs/DelayHandle",
                "MyProject/Private/Game/Libs/EventHandle",
                "MyProject/Private/Game/Libs/FrameHandle",

                "MyProject/Private/Game/Libs/Resource/ResLoad",
                "MyProject/Private/Game/Libs/Resource/ResLoadData",
                "MyProject/Private/Game/Libs/Resource/RefAsync",

                "MyProject/Private/Game/Libs/ObjectPool",

                // UI 区域
                "MyProject/Private/Game/UI/UIPack",
                "MyProject/Private/Game/UI/UITestCanvas",

                // Test 区域
                "MyProject/Private/Game/UnitTest",

                // 其它
                "MyProject/Private/UI/Widgets",
	        }
        );

		PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "OnlineSubsystem",
				"OnlineSubsystemUtils",
                "Sockets",
                "Networking"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
				"Slate",
				"SlateCore",
                "UMG",
			}
        );

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            Definitions.Add("_CRT_SECURE_NO_WARNINGS");
        }
        //Definitions.Add("WIN32_LEAN_AND_MEAN");
        //Definitions.Add("_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH");
        //Definitions.Add("NO_GETADDRINFO");
        //Definitions.Add("ENABLE_EXCEPTIONS");
        //Definitions.Add("ENABLE_DETACH");

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        //PrivateIncludePaths.AddRange(
        //    new string[] {
        //        "Coupling/Private",
        //        // ... add other private include paths required here ...
        //        Path.Combine(ThirdPartyPath, "v8", "include"),
        //    }
        //);

        //PublicDependencyModuleNames.AddRange(
        //    new string[]
        //    {
        //        "Engine",
        //        "Core",
        //        // ... add other public dependencies that you statically link with here ...
        //    }
        //);

        //PrivateDependencyModuleNames.AddRange(
        //    new string[]
        //    {
        //        // ... add private dependencies that you statically link with here ...
        //    }
        //);

        //DynamicallyLoadedModuleNames.AddRange(
        //    new string[]
        //    {
        //        // ... add any modules that your module loads dynamically here ...
        //    }
        //);

        loadThirdPartyInclude();
        LoadSockets(Target);
        LoadTestExtern(Target);
        LoadGtest(Target);
        LoadLua(Target);
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

    private void loadThirdPartyInclude()
    {
        PublicIncludePaths.AddRange(
            new string[] 
            {
                // ... add public include paths required here ...
                Path.Combine(ThirdPartyPath, "Inc"),
                Path.Combine(ThirdPartyPath, "Inc", "Lua"),
            }
        );
    }

    private bool LoadSockets_bak(TargetInfo Target)
    {
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            string PlatformString;
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Sockets");

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                //PlatformString = "x64";
                //LibrariesPath = Path.Combine(LibrariesPath, "Win64");

                if (Target.Configuration == UnrealTargetConfiguration.Debug)
                {
                    LibrariesPath = Path.Combine(LibrariesPath, "Debug");
                }
            }
            else
            {
                //PlatformString = "ia32";
                //LibrariesPath = Path.Combine(LibrariesPath, "Win32");
            }

            //LibrariesPath = Path.Combine(LibrariesPath, "Debug");

            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icui18n.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icuuc.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_base.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_libbase.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_nosnapshot.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_snapshot.lib"));

            //PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "v8", "Includes"));

            //Definitions.Add(string.Format("WITH_COUPLING=1"));

            if (Target.Configuration == UnrealTargetConfiguration.Debug)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Sockets.lib"));
            }
            else
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Sockets.lib"));
            }

            return true;
        }

        //Definitions.Add(string.Format("WITH_COUPLING=0"));
        return false;
    }

    private bool LoadSockets(TargetInfo Target)
    {
        string LibrariesPath;

        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Sockets", "Sockets_d.lib");
        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }

    private bool LoadTestExtern(TargetInfo Target)
    {
        string LibrariesPath;
        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "TestStaticLib", "TestStaticLib_d.lib");

        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }

    private bool LoadGtest(TargetInfo Target)
    {
        string LibrariesPath;

        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "gtest", "gtest_d.lib");
        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }

    // 加载 Lua
    private bool LoadLua(TargetInfo Target)
    {
        string LibrariesPath;

        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Lua", "Lua_d.lib");
        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }
}

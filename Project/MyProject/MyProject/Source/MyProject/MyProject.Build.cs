// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

/**
 * @reference https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 * Engine\Source\Programs\UnrealBuildTool\Platform\Windows\VCToolChain.cs
 * // NOTE: Uncommenting this line will print includes as they are encountered by the preprocessor.  This can help with diagnosing include order problems.
 * if (WindowsPlatform.bCompileWithClang && !WindowsPlatform.bUseVCCompilerArgs)
 * {
 *	   //Arguments.Add("-H");
 * }
 * else
 * {
 *	   //Arguments.Add("/showIncludes");
 * }
 */
public class MyProject : ModuleRules
{
    //public MyProject(TargetInfo Target)
    // 4.17
    public MyProject(ReadOnlyTargetRules Target) : base(Target)
    {
		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
		//this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// UE4 4.22
		// warning: Modules must specify an explicit precompiled header (eg.PrivatePCHHeaderFile = "Public/MyEngine/MyProject.h") from UE 4.21 onwards.
		this.PrivatePCHHeaderFile = "Public/MyEngine/MyProject.h";

		// UE4 4.17
		this.bUseRTTI = true;
        // warning CS0618: “UnrealBuildTool.ModuleRules.UEBuildConfiguration”已过时:“The UEBuildConfiguration alias is deprecated in 4.18. Set the same properties on the ReadOnlyTargetRules instance passed into the ModuleRules constructor instead.”
        // UE 4.18

        // Engine\Source\Programs\UnrealBuildTool\Configuration\ModuleRules.cs
        // this.PCHUsage = PCHUsageMode.Default;

        // https://docs.unrealengine.com/en-us/Programming/UnrealBuildSystem/Configuration
        // http://api.unrealengine.com/CHN/Programming/UnrealBuildSystem/Configuration/
        this.MinFilesUsingPrecompiledHeaderOverride = 1;
        // 仅仅需要编译修改的少数几个文件
        bFasterWithoutUnity = true;
        // 全部重新编译
        //this.bFasterWithoutUnity = false;

        // 添加类似 VS 工程中的包含目录，头文件就是相对于这些目录的
        // Engine\Plugins\Developer\BlankPlugin\Source\BlankPlugin\BlankPlugin.Build.cs
        this.PrivateIncludePaths.AddRange(
            new string[] {
				// MyProject 尽量包含目录只包含 MyProject/Private 和 MyProject/Public， 这样别的模块如果引用当前模块，就只需要添加包含模块 MyProject，这样就会添加包含目录 MyProject/Private 和 MyProject/Public 引用的模块就不用添加这么多包含目录了，包含目录是指 MyProject.Build.cs 所在目录开始加上子目录，例如 MyProject.Build.cs 所在目录 MyProject ，然后加子目录 MyProject/aaa, MyProject/bbb 
                // Relative to MyProject/Plugins/MyScriptPlugin/Source , 包含插件头文件， MyProject\MyProject.uproject 包含插件根目录 AdditionalPluginDirectories
                // ScriptPlugin 包含目录
			    //"ScriptPlugin/Classes",
                //"ScriptPlugin/Private",

                // Player 区域
                "MyProject/Private/MyEngine",
                "MyProject/Private/MyEngine/UI/Widgets",
                "MyProject/Private/MyEngine/Persist",
                "MyProject/Private/MyEngine/MyActor",
                "MyProject/Private/MyEngine/Math",
                "MyProject/Private/MyEngine/Misc",
                "MyProject/Private/MyEngine/Network",
                "MyProject/Private/MyEngine/Network/Web",
                "MyProject/Private/MyEngine/MyAsset",
                "MyProject/Private/MyEngine/MyBluePrint",

                "MyProject/Private/MyEngine/MyBase",
                "MyProject/Private/MyEngine/MyBase/Actor",
                "MyProject/Private/MyEngine/MyBase/Frame",
                "MyProject/Private/MyEngine/MyBase/AI",
                "MyProject/Private/MyEngine/MyBase/Anim",
                "MyProject/Private/MyEngine/MyBase/Delegate",
                "MyProject/Private/MyEngine/MyBase/Misc",
                "MyProject/Private/MyEngine/MyBase/HAL",
                "MyProject/Private/MyEngine/MyBase/Tick",

                "MyProject/Private/MyEngine/MyFly",
                "MyProject/Private/MyEngine/MyFly/Actor",
                "MyProject/Private/MyEngine/MyFly/Frame",
                "MyProject/Private/MyEngine/MyFly/AI",
                "MyProject/Private/MyEngine/MyFly/Anim",

                "MyProject/Private/MyEngine/MyTP",
                "MyProject/Private/MyEngine/MyTP/Actor",
                "MyProject/Private/MyEngine/MyTP/Frame",
                "MyProject/Private/MyEngine/MyTP/AI",
                "MyProject/Private/MyEngine/MyTP/Anim",

                "MyProject/Private/MyEngine/MyTom",
                "MyProject/Private/MyEngine/MyTom/Actor",
                "MyProject/Private/MyEngine/MyTom/Frame",
                "MyProject/Private/MyEngine/MyTom/AI",
                "MyProject/Private/MyEngine/MyTom/Anim",

                // Libs 区域
                "MyProject/Private/BaseFrame/Libs/Common",
				"MyProject/Private/BaseFrame/Libs/Common/MiniInc",
				"MyProject/Private/BaseFrame/Libs/Common/ObjectAsset",

				"MyProject/Private/BaseFrame/Libs/DataStruct",
				"MyProject/Private/BaseFrame/Libs/DataStruct/IndexList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/KeyIndexList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/LinkedList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList/NoPriorityList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList/PriorityList",

				"MyProject/Private/BaseFrame/Libs/EngineWrap",
				"MyProject/Private/BaseFrame/Libs/FrameWork",
				"MyProject/Private/BaseFrame/Libs/FrameWork/Layer",
				"MyProject/Private/BaseFrame/Libs/NetWork/Socket",
				"MyProject/Private/BaseFrame/Libs/NetWork/NetCmdDispatch",
				"MyProject/Private/BaseFrame/Libs/NetWork/Web",

				"MyProject/Private/BaseFrame/Libs/Ui/Base",
				"MyProject/Private/BaseFrame/Libs/Ui/Widget",
				"MyProject/Private/BaseFrame/Libs/Ui/Widget/TreeWidget",

				"MyProject/Private/BaseFrame/Libs/Log",
				"MyProject/Private/BaseFrame/Libs/Table",
				"MyProject/Private/BaseFrame/Libs/Table/ItemObject",
				"MyProject/Private/BaseFrame/Libs/Tools",
				"MyProject/Private/BaseFrame/Libs/Input",

				"MyProject/Private/BaseFrame/Libs/Thread",
                "MyProject/Private/BaseFrame/Libs/MySimpleDelegate",
                "MyProject/Private/BaseFrame/Libs/Tools",
                "MyProject/Private/BaseFrame/Libs/DelayHandle",
                "MyProject/Private/BaseFrame/Libs/EventHandle",
                "MyProject/Private/BaseFrame/Libs/FrameHandle",

                "MyProject/Private/BaseFrame/Libs/Resource/ResLoad",
                "MyProject/Private/BaseFrame/Libs/Resource/ResLoad/LoadItem",
                "MyProject/Private/BaseFrame/Libs/Resource/ResLoad/ResourceItem",
                "MyProject/Private/BaseFrame/Libs/Resource/ResLoadData",
                "MyProject/Private/BaseFrame/Libs/Resource/RefAsync",
                "MyProject/Private/BaseFrame/Libs/Resource/InsResMgr",
                "MyProject/Private/BaseFrame/Libs/Resource/InsRes",
                "MyProject/Private/BaseFrame/Libs/Resource/Download",
                "MyProject/Private/BaseFrame/Libs/Resource/DelayTask",
                "MyProject/Private/BaseFrame/Libs/Resource/Version",
                "MyProject/Private/BaseFrame/Libs/Resource/AutoUpdate",

                "MyProject/Private/BaseFrame/Libs/Pool",
                "MyProject/Private/BaseFrame/Libs/MsgRoute",
                "MyProject/Private/BaseFrame/Libs/FileSystem",
                "MyProject/Private/BaseFrame/Libs/Math",
                "MyProject/Private/BaseFrame/Libs/Task",
                "MyProject/Private/BaseFrame/Libs/Core",
                "MyProject/Private/BaseFrame/Libs/Core/Object",
                "MyProject/Private/BaseFrame/Libs/Core/Templates",
                "MyProject/Private/BaseFrame/Libs/Core/Rtti",
                "MyProject/Private/BaseFrame/Libs/Core/Platform",
                "MyProject/Private/BaseFrame/Libs/Core/Memory",
                "MyProject/Private/BaseFrame/Libs/Core/Tools",

                "MyProject/Private/BaseFrame/Libs/LuaBind",
                "MyProject/Private/BaseFrame/Libs/LuaCBridge",
                "MyProject/Private/BaseFrame/Libs/Scene",
                "MyProject/Private/BaseFrame/Libs/Scene/SceneEntityBase",

                "MyProject/Private/BaseFrame/Libs/Auxiliary/AuxLoader",
                "MyProject/Private/BaseFrame/Libs/Auxiliary/AuxUi",
                "MyProject/Private/BaseFrame/Libs/Auxiliary/AuxBase",
                "MyProject/Private/BaseFrame/Libs/Auxiliary/AuxUserData",

                "MyProject/Private/BaseFrame/Libs/Engine",
                "MyProject/Private/BaseFrame/Libs/Engine/HAL",
                "MyProject/Private/BaseFrame/Libs/Engine/MyDelegate",
                "MyProject/Private/BaseFrame/Libs/Engine/Templates",
                "MyProject/Private/BaseFrame/Libs/Misc",

				"MyProject/Private/BaseFrame/App",
				"MyProject/Private/BaseFrame/App/Module/Game",
				"MyProject/Private/BaseFrame/App/Module/Game/EventNotify",
				"MyProject/Private/BaseFrame/App/Module/Game/GameNetHandle",
				"MyProject/Private/BaseFrame/App/Module/Game/RouteMsgHandle",

				"MyProject/Private/BaseFrame/App/Frame",

				"MyProject/Private/BaseFrame/App/Common/FrameWork",
				"MyProject/Private/BaseFrame/App/Common/ProjectData",
				"MyProject/Private/BaseFrame/App/Common/Scene",
				"MyProject/Private/BaseFrame/App/Common/Scene/SceneState",
				"MyProject/Private/BaseFrame/App/Common/Scene/Being",
				"MyProject/Private/BaseFrame/App/Common/Scene/BeingRender",
				"MyProject/Private/BaseFrame/App/Common/Common",
				"MyProject/Private/BaseFrame/App/Common/Module",

                // UI 区域
                "MyProject/Private/BaseFrame/Ui/UiPack",
                "MyProject/Private/BaseFrame/Ui/UiTestCanvas",
                "MyProject/Private/BaseFrame/Ui/UiCustomButton",
                "MyProject/Private/BaseFrame/Ui/UiLoadStyles",
                "MyProject/Private/BaseFrame/Ui/UiChat",
                "MyProject/Private/BaseFrame/Ui/UiLog",
                "MyProject/Private/BaseFrame/Ui/UiEditText",
                "MyProject/Private/BaseFrame/Ui/UiSlateTab",
                "MyProject/Private/BaseFrame/Ui/UiSlateStyleSet",
                "MyProject/Private/BaseFrame/Ui/UiTestUMG",
                "MyProject/Private/BaseFrame/Ui/UiFunctionBar",

                // Test 区域
                "MyProject/Private/BaseFrame/UnitTest",
                "MyProject/Private/BaseFrame/UnitTest/TestBase",
                "MyProject/Private/BaseFrame/UnitTest/TestUi",
                "MyProject/Private/BaseFrame/UnitTest/TestDownload",
                "MyProject/Private/BaseFrame/UnitTest/TestNetClientBuffer",
                "MyProject/Private/BaseFrame/UnitTest/TestOther",
                "MyProject/Private/BaseFrame/UnitTest/TestLuaBind",
                "MyProject/Private/BaseFrame/UnitTest/TestPak",
                "MyProject/Private/BaseFrame/UnitTest/TestAsset",

                // Example
                "MyProject/Private/BaseFrame/Example/AccessMesh",
                "MyProject/Private/BaseFrame/Example/AnimateVertexPositions",
                "MyProject/Private/BaseFrame/Example/AnimationCppAndBlueprint",
                "MyProject/Private/BaseFrame/Example/AnimNode",

                "MyProject/Private/BaseFrame/Example/AsyncLoad",
                "MyProject/Private/BaseFrame/Example/ClearWidgets",
                "MyProject/Private/BaseFrame/Example/CoordinateMapping",
                "MyProject/Private/BaseFrame/Example/CppAndBlueprint",

                "MyProject/Private/BaseFrame/Example/CustomActorIcon",
                "MyProject/Private/BaseFrame/Example/CustomComponents",
                "MyProject/Private/BaseFrame/Example/DeferAttachToSocket",
                "MyProject/Private/BaseFrame/Example/DelegatesInCppBP",

                "MyProject/Private/BaseFrame/Example/DistanceToCollision",
                "MyProject/Private/BaseFrame/Example/DynamicLoadObject",
                "MyProject/Private/BaseFrame/Example/EnumToString",
                "MyProject/Private/BaseFrame/Example/EventHand",

                "MyProject/Private/BaseFrame/Example/ExtendUserWidget",
                "MyProject/Private/BaseFrame/Example/FileAndPath",
                "MyProject/Private/BaseFrame/Example/InterfaceImpl",
                "MyProject/Private/BaseFrame/Example/LogMacro",

                "MyProject/Private/BaseFrame/Example/ModularPawn",
                "MyProject/Private/BaseFrame/Example/MultiThread",
                "MyProject/Private/BaseFrame/Example/ObjectIterator",
                "MyProject/Private/BaseFrame/Example/ObjectLibraryLoad",

                "MyProject/Private/BaseFrame/Example/RWConfigFile",
                "MyProject/Private/BaseFrame/Example/SubclassAccess",
                "MyProject/Private/BaseFrame/Example/TaskGraphSystem",
                "MyProject/Private/BaseFrame/Example/UmgExtendInCpp",

                "MyProject/Private/BaseFrame/Example/UmgInCpp",
            }
        );

        PublicIncludePaths.AddRange(
            new string[] {
                "MyProject/Public/MyEngine",
                "MyProject/Public/MyEngine/Ui",
                // Plugin 需要单独包含头文件
                // Relative to Engine\Plugins\Runtime\ApexDestruction\Source , 包含插件头文件
                // DestructibleActor.h 包含目录
			    "../../../../../ApexDestruction/Public",
            }
        );

        // 添加需要包含的 Public 模块，包括头文件目录，库文件目录和库文件名字
        this.PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine",
                "EngineSettings",   // UGameMapsSettings
                "OnlineSubsystem",
				"OnlineSubsystemUtils",
                "Sockets",
                "Networking",
                "UMG",
                "PakFile",
                "PhysX",    // PhysX
                "APEX",     // PhysX
                "SandboxFile",  // IPlatformFileSandboxWrapper.h，否则链接不过
                //"DesktopPlatform", // IDesktopPlatform.h，注意移动平台需要注释掉

                //"UnrealEd", // UUnrealEdEngine \ UEditorEngine
                "ApplicationCore",  // "HAL/PlatformApplicationMisc.h" 中的 FPlatformApplicationMisc::ClipboardCopy
                "ScriptPlugin",     // ScriptPlugin 插件
				"AssetRegistry",	// AssetDataTagMap.h
				"Json",				// Json
				"JsonUtilities",	// Json
				"XmlParser",		// Xml
			}
        );

        // 添加需要包含的 Private 模块，包括头文件目录，库文件目录和库文件名字
        this.PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",  // CoreUObject\Private\Serialization\AsyncLoadingThread.h
                "ApexDestruction",  // Engine\Plugins\Runtime\ApexDestruction\Source\ApexDestructionEditor\ApexDestructionEditor.Build.cs
                "ApexDestructionLib", // Engine\Plugins\Runtime\ApexDestruction\Source\ApexDestructionEditor\ApexDestructionEditor.Build.cs
                "InputCore",
				"Slate",
				"SlateCore",
                "UMG",
                "HTTP",
                "PakFile",
                "ApplicationCore",  // "HAL/PlatformApplicationMisc.h" 中的 FPlatformApplicationMisc::ClipboardCopy
                "ScriptPlugin",     // ScriptPlugin 插件
                // error : Could not find definition for module 'MyScriptPlugin' (referenced via Target -> MyProject.Build.cs)
                //"MyScriptPlugin",     // ScriptPlugin 插件
                "NavigationSystem",     // UE 4.20 error LNK2019: unresolved external symbol "__declspec(dllimport) public: static class UClass * __cdecl UNavigationSystemV1::StaticClass(void)" (__imp_?StaticClass@UNavigationSystemV1@@SAPEAVUClass@@XZ), 不添加会有链接错误， 4.20 之前如果不添加 NavigationSystem 引用，直接使用时没有链接错误的
            }
        );

        // warning CS0618: “UnrealBuildTool.ModuleRules.UEBuildConfiguration”已过时:“The UEBuildConfiguration alias is deprecated in 4.18. Set the same properties on the ReadOnlyTargetRules instance passed into the ModuleRules constructor instead.”
        //if (UEBuildConfiguration.bBuildEditor == true)
        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }

        // AnimGraphRuntime 模块的包含目录需要这样导入，参考 Engine.Build.cs
        this.DynamicallyLoadedModuleNames.Add("AnimGraphRuntime");
        // error: Module rules for 'MyProject' should not be dependent on modules which are also dynamically loaded: ScriptPlugin
        //DynamicallyLoadedModuleNames.Add("ScriptPlugin");

        // 包含 Private 模块中的头文件目录
        //PrivateIncludePathModuleNames.AddRange(
        //    new string[] {
        //        "HTTP"
        //    }
        //);

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            // UE 4.9.1 warning CS0618: “UnrealBuildTool.ModuleRules.Definitions”已过时:“The 'Definitions' property has been deprecated. Please use 'PublicDefinitions' instead.”
            //Definitions.Add("_CRT_SECURE_NO_WARNINGS");
            //Definitions.Add("__WIN32__");
            PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
            PublicDefinitions.Add("__WIN32__");
            // VS 2017: error C4668: '_WIN32_WINNT_WIN10_TH2' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
            // 添加后出现 warning C4005: 'WIN32_LEAN_AND_MEAN': macro redefinition
            PublicDefinitions.Add("WIN32_LEAN_AND_MEAN");
        }
        //Definitions.Add("WIN32_LEAN_AND_MEAN");
        //Definitions.Add("_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH");
        //Definitions.Add("NO_GETADDRINFO");
        //Definitions.Add("ENABLE_EXCEPTIONS");
        //Definitions.Add("ENABLE_DETACH");

        //PrivateIncludePaths.AddRange(
        //    new string[] {
        //        "Coupling/Private",
        //        // ... add other private include paths required here ...
        //        Path.Combine(this.getMyProjectThirdPartyPath(), "v8", "include"),
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

        // 添加对第三方库 PhysX_3.4 的引用头文件
        // 现在接口参数修改了
        //AddEngineThirdPartyPrivateStaticDependencies(Target,
        //    "PhysX",
        //    "APEX"
        //    );
        // 4.17 需要新的接口
        this.AddEngineThirdPartyPrivateStaticDependencies(Target, "PhysX");
        this.AddEngineThirdPartyPrivateStaticDependencies(Target, "APEX");

        //PublicSystemIncludePaths.Add("ThirdParty/hlslcc/hlslcc/src/hlslcc_lib");
        //RuntimeDependencies.Add(new RuntimeDependency("$(EngineDir)/Binaries/ThirdParty/ARM/Win32/astcenc.exe"));
        //string APEXDir = UEBuildConfiguration.UEThirdPartySourceDirectory + "PhysX/" + ApexVersion + "/";

        //if (UEBuildConfiguration.bBuildEditor == true)
        //{

        //    PublicDependencyModuleNames.AddRange(
        //        new string[] {
        //            "MyProjectEditor"
        //        }
        //    );

        //    CircularlyReferencedDependentModules.AddRange(
        //        new string[] {
        //            "MyProjectEditor",
        //        }
        //    );
        //}

        //LoadMyProjectEditor(Target);

        /**
         * @url https://docs.unrealengine.com/en-us/Programming/UnrealBuildSystem/Configuration
         * UnrealBuildTool reads settings from XML configuration files in the following locations:
         * Engine/Saved/UnrealBuildTool/BuildConfiguration.xml
         * User Folder/AppData/Roaming/Unreal Engine/UnrealBuildTool/BuildConfiguration.xml
         * My Documents / Unreal Engine / UnrealBuildTool / BuildConfiguration.xml
         * These files are added to the generated UE4 project under the Config/UnrealBuildTool folder.
         * 
         * @brief 自己新加的配置文件
         * MyProject\Config\UnrealBuildTool\BuildConfiguration.xml
         */
        // 
        //UEBuildConfiguration.BuildConfiguration.bForceDebugUnrealHeaderTool = true;

        // 添加 ScriptPlugin 目录
        //string path = Path.Combine(this.getMyProjectPluginsPath(), "MyScriptPlugin/Source/ScriptPlugin");
        //PublicLibraryPaths.Add(path);

        this.loadThirdPartyInc();

        //LoadSockets(Target);
        //this.LoadTestExtern(Target);
        //LoadGtest(Target);
        //this.LoadLua(Target);
        //this.LoadLuaSocket(Target);

        this.loadThirdLib(Target, "Lua");
        this.loadThirdLib(Target, "LuaSocket");
    }

    /**
     * @brief 获取自己模块目录
     */
    protected string getMyModulePath()
    {
        // “UnrealBuildTool.RulesCompiler.GetModuleFilename(string)”已过时:“GetModuleFilename is deprecated, use the ModuleDirectory property on any ModuleRules instead to get a path to your module.”
        //return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
        //return Path.GetDirectoryName(ModuleDirectory);    // 不是这样获取
        return ModuleDirectory;      // 参照 Engine\Plugins\Runtime\Nvidia\Ansel\Source\Ansel\Ansel.Build.cs 实现
    }

    protected string getMyProjectPluginsPath()
    {
        string ret = "";
        ret = Path.GetFullPath(Path.Combine(this.getMyModulePath(), "../..", "Plugins"));
        return ret;
    }

    /**
     * @brief 获取自己工程的第三方目录
     */
    protected string getMyProjectThirdPartyPath()
    {
        string ret = "";

        ret = Path.GetFullPath(Path.Combine(this.getMyModulePath(), "../..", "ThirdParty"));

        return ret;
    }

    /**
     * @brief 获取引擎第三方目录
     */
    protected string getEngineThirdPartyPath()
    {
        string ret = "";

        ret = Target.UEThirdPartySourceDirectory;

        return ret;
    }

    private void loadThirdPartyInc()
    {
        PublicIncludePaths.AddRange(
            new string[] 
            {
                // ... add public include paths required here ...
                Path.Combine(this.getMyProjectThirdPartyPath(), "Inc"),
                Path.Combine(this.getMyProjectThirdPartyPath(), "Inc", "Lua"),
                //Path.Combine(this.getMyProjectThirdPartyPath(), "Inc", "LuaBridge"),
                Path.Combine(this.getMyProjectThirdPartyPath(), "Inc", "LuaSocket"),
            }
        );
    }

    // https://wiki.unrealengine.com/Linking_Static_Libraries_Using_The_Build_System
    //private bool LoadSockets_bak(TargetInfo Target)
    // 4.17
    //private bool LoadSockets_bak(ReadOnlyTargetRules Target)
    //{
    //    // https://wiki.unrealengine.com/Integrating_OpenCV_Into_Unreal_Engine_4
    //    // UE4.9.1 error CS0122: “UnrealBuildTool.BuildConfiguration”不可访问，因为它受保护级别限制
    //    //bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT;
    //    bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT;

    //    if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
    //    {
    //        //string PlatformString;
    //        string LibrariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Sockets");

    //        if (Target.Platform == UnrealTargetPlatform.Win64)
    //        {
    //            //PlatformString = "x64";
    //            //LibrariesPath = Path.Combine(LibrariesPath, "Win64");

    //            if (Target.Configuration == UnrealTargetConfiguration.Debug)
    //            {
    //                LibrariesPath = Path.Combine(LibrariesPath, "Debug");
    //            }
    //        }
    //        else
    //        {
    //            //PlatformString = "ia32";
    //            //LibrariesPath = Path.Combine(LibrariesPath, "Win32");
    //        }

    //        //LibrariesPath = Path.Combine(LibrariesPath, "Debug");

    //        //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icui18n.lib"));
    //        //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icuuc.lib"));
    //        //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_base.lib"));
    //        //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_libbase.lib"));
    //        //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_nosnapshot.lib"));
    //        //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_snapshot.lib"));

    //        //PublicIncludePaths.Add(Path.Combine(this.getMyProjectThirdPartyPath(), "v8", "Includes"));

    //        //Definitions.Add(string.Format("WITH_COUPLING=1"));

    //        if (Target.Configuration == UnrealTargetConfiguration.Debug)
    //        {
    //            // 添加库目录
    //            // PublicLibraryPaths.Add(LuaLibDirectory);
    //            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Sockets.lib"));

    //            //Add Dynamic Libraries (Debug Version)
    //            //PublicDelayLoadDLLs.Add("opencv_world300d.dll");
    //        }
    //        else
    //        {
    //            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Sockets.lib"));
    //        }

    //        return true;
    //    }

    //    //Definitions.Add(string.Format("WITH_COUPLING=0"));
    //    return false;
    //}

    //private bool LoadSockets(TargetInfo Target)
    // 4.17
    //private bool LoadSockets(ReadOnlyTargetRules Target)
    //{
    //    string LibrariesPath;

    //    LibrariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Sockets", "Sockets_d.lib");
    //    PublicAdditionalLibraries.Add(LibrariesPath);

    //    return true;
    //}

    //private bool LoadTestExtern(TargetInfo Target)
    // 4.17
    //private bool LoadTestExtern(ReadOnlyTargetRules Target)
    //{
    //    string LibrariesPath;
    //    LibrariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "TestStaticLib", "TestStaticLib_d.lib");

    //    PublicAdditionalLibraries.Add(LibrariesPath);

    //    return true;
    //}

    //private bool LoadGtest(TargetInfo Target)
    // 4.17
    //private bool LoadGtest(ReadOnlyTargetRules Target)
    //{
    //    string LibrariesPath;

    //    LibrariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "gtest", "gtest_d.lib");
    //    PublicAdditionalLibraries.Add(LibrariesPath);

    //    return true;
    //}

    // 加载 Lua
    //private bool LoadLua(TargetInfo Target)
    // 4.17
    //private bool LoadLua(ReadOnlyTargetRules Target)
    //{
    //    string librariesPath = "";

    //    if (UnrealTargetPlatform.Mac == Target.Platform)
    //    {

    //    }
    //    else if(UnrealTargetPlatform.Win32 == Target.Platform)
    //    {
    //        /**
    //         * @brief bDebugBuildsActuallyUseDebugCRT 开启这个会有很多链接错误，因此暂时不开启
    //         * @ref Engine\Source\Programs\UnrealBuildTool\Configuration\TargetRules.cs
    //         * @ref Engine\Saved\UnrealBuildTool\BuildConfiguration.xml
    //         */
    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win32", "Lua_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //        else
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win32", "Lua.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.Win64 == Target.Platform)
    //    {
    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win64", "Lua_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //        else
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win64", "Lua.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.Android == Target.Platform)
    //    {
    //        // UE4.19.1 error CS0122: “UnrealBuildTool.BuildConfiguration”不可访问，因为它受保护级别限制
    //        //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
    //        //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

    //        // UE4.19.1 warning CS0618: “UnrealBuildTool.ModuleRules.ReceiptPropertyList.Add(UnrealBuildTool.ReceiptProperty)”已过时:“Constructing a ReceiptProperty object is deprecated. Call RuntimeDependencies.Add() with the path to the file to stage.”
    //        //AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));
    //        //RuntimeDependencies.Add(Path.Combine(BuildPath, "My_APL_armv7.xml"));

    //        //PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLua.so");

    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/armv7");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/arm64");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/x86");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/x86_64");
    //        PublicLibraryPaths.Add(librariesPath);

    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            PublicAdditionalLibraries.Add("Lua_d");
    //        }
    //        else
    //        {
    //            PublicAdditionalLibraries.Add("Lua");
    //        }
    //    }
    //    else if (UnrealTargetPlatform.IOS == Target.Platform)
    //    {

    //    }
    //    else
    //    {
    //        throw new System.Exception("Not support platform");
    //    }

    //    return true;
    //}

    //private bool LoadLuaSocket(TargetInfo Target)
    // 4.17
    //private bool LoadLuaSocket(ReadOnlyTargetRules Target)
    //{
    //    /**
    //     * @brief UnrealTargetPlatform
    //     * @url Engine\Source\Programs\UnrealBuildTool\Configuration\UEBuildTarget.cs
    //     */
    //    string librariesPath = "";

    //    if (UnrealTargetPlatform.Mac == Target.Platform)
    //    {

    //    }
    //    else if(UnrealTargetPlatform.Win32 == Target.Platform)
    //    {
    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LuaSocket", "Win32", "LuaSocket_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //        else
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LuaSocket", "Win32", "LuaSocket.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.Win64 == Target.Platform)
    //    {
    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT*/)
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LuaSocket", "Win64", "LuaSocket_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //        else
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LuaSocket", "Win64", "LuaSocket_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.Android == Target.Platform)
    //    {
    //        /**
    //         * @brief AndroidToolChain
    //         * @url Engine\Source\Programs\UnrealBuildTool\Platform\Android\AndroidToolChain.cs
    //         * @ref Engine\Source\ThirdParty\GoogleVR\GoogleVR.Build.cs
    //         * @brief Target.UEThirdPartySourceDirectory \ 
    //         */
    //        // error CS0122: “UnrealBuildTool.BuildConfiguration”不可访问，因为它受保护级别限制
    //        // string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
    //        //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

    //        // UE4.19.1 warning CS0618: “UnrealBuildTool.ModuleRules.ReceiptPropertyList.Add(UnrealBuildTool.ReceiptProperty)”已过时:“Constructing a ReceiptProperty object is deprecated. Call RuntimeDependencies.Add() with the path to the file to stage.”
    //        //AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));
    //        //RuntimeDependencies.Add(Path.Combine(BuildPath, "My_APL_armv7.xml"));

    //        //PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLuaSocket.so");

    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LibSocket", "Android/armv7");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LibSocket", "Android/arm64");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LibSocket", "Android/x86");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "LibSocket", "Android/x86_64");
    //        PublicLibraryPaths.Add(librariesPath);

    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            PublicAdditionalLibraries.Add("libLuaSocket_d");
    //        }
    //        else
    //        {
    //            PublicAdditionalLibraries.Add("libLuaSocket");
    //        }
    //    }
    //    else if (UnrealTargetPlatform.IOS == Target.Platform)
    //    {

    //    }
    //    else
    //    {
    //        throw new System.Exception("Not support platform");
    //    }

    //    return true;
    //}

    // 加载 ProjectEditor
    //private bool LoadMyProjectEditor(TargetInfo Target)
    // 4.17
    private bool LoadMyProjectEditor(ReadOnlyTargetRules Target)
    {
        // warning CS0618: “UnrealBuildTool.ModuleRules.BuildConfiguration”已过时:“The BuildConfiguration alias is deprecated in 4.18. Set the same properties on the ReadOnlyTargetRules instance passed into the ModuleRules constructor instead.”
        //if (UEBuildConfiguration.bBuildEditor == true)
        if (Target.bBuildEditor == true)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "MyProjectEditor"
                }
            );

            CircularlyReferencedDependentModules.AddRange(
                new string[] {
                    "MyProjectEditor",
                }
            );
        }

        return true;
    }

    //private bool loadThirdLib(ReadOnlyTargetRules Target, string libName)
    //{
    //    string librariesPath = "";

    //    if (UnrealTargetPlatform.Mac == Target.Platform)
    //    {

    //    }
    //    else if (UnrealTargetPlatform.Win32 == Target.Platform)
    //    {
    //        /**
    //         * @brief bDebugBuildsActuallyUseDebugCRT 开启这个会有很多链接错误，因此暂时不开启
    //         * @ref Engine\Source\Programs\UnrealBuildTool\Configuration\TargetRules.cs
    //         * @ref Engine\Saved\UnrealBuildTool\BuildConfiguration.xml
    //         */
    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win32", libName + "_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //        else
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win32", libName + ".lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.Win64 == Target.Platform)
    //    {
    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win64", libName + "_d.lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //        else
    //        {
    //            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Win64", libName + ".lib");
    //            PublicAdditionalLibraries.Add(librariesPath);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.Android == Target.Platform)
    //    {
    //        // UE4.19.1 error CS0122: “UnrealBuildTool.BuildConfiguration”不可访问，因为它受保护级别限制
    //        //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
    //        //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

    //        // UE4.19.1 warning CS0618: “UnrealBuildTool.ModuleRules.ReceiptPropertyList.Add(UnrealBuildTool.ReceiptProperty)”已过时:“Constructing a ReceiptProperty object is deprecated. Call RuntimeDependencies.Add() with the path to the file to stage.”
    //        //AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));
    //        //RuntimeDependencies.Add(Path.Combine(BuildPath, "My_APL_armv7.xml"));

    //        //PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLua.so");

    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/armv7");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/arm64");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/x86");
    //        PublicLibraryPaths.Add(librariesPath);
    //        librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Android/x86_64");
    //        PublicLibraryPaths.Add(librariesPath);

    //        if (UnrealTargetConfiguration.Debug == Target.Configuration/* &&
    //            Target.bDebugBuildsActuallyUseDebugCRT */)
    //        {
    //            PublicAdditionalLibraries.Add(libName + "_d");
    //        }
    //        else
    //        {
    //            PublicAdditionalLibraries.Add(libName);
    //        }
    //    }
    //    else if (UnrealTargetPlatform.IOS == Target.Platform)
    //    {

    //    }
    //    else
    //    {
    //        throw new System.Exception("Not support platform");
    //    }

    //    return true;
    //}

    private bool loadThirdLib(ReadOnlyTargetRules Target, string libName)
    {
        string librariesPath = "";

        if (UnrealTargetPlatform.Mac == Target.Platform)
        {

        }
        else if (UnrealTargetPlatform.Win32 == Target.Platform)
        {
            if (UnrealTargetConfiguration.Debug == Target.Configuration)
            {
                librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Win32", libName + "_d.lib");
                PublicAdditionalLibraries.Add(librariesPath);
            }
            else
            {
                librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Win32", libName + ".lib");
                PublicAdditionalLibraries.Add(librariesPath);
            }
        }
        else if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            if (UnrealTargetConfiguration.Debug == Target.Configuration)
            {
                librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Win64", libName + "_d.lib");
                PublicAdditionalLibraries.Add(librariesPath);
            }
            else
            {
                librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Win64", libName + ".lib");
                PublicAdditionalLibraries.Add(librariesPath);
            }
        }
        else if (UnrealTargetPlatform.Android == Target.Platform)
        {
            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Android/armv7");
            PublicLibraryPaths.Add(librariesPath);
            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Android/arm64");
            PublicLibraryPaths.Add(librariesPath);
            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Android/x86");
            PublicLibraryPaths.Add(librariesPath);
            librariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", libName, "Android/x86_64");
            PublicLibraryPaths.Add(librariesPath);

            if (UnrealTargetConfiguration.Debug == Target.Configuration)
            {
                PublicAdditionalLibraries.Add(libName + "_d");
            }
            else
            {
                PublicAdditionalLibraries.Add(libName);
            }
        }
        else if (UnrealTargetPlatform.IOS == Target.Platform)
        {

        }
        else
        {
            throw new System.Exception("Not support platform");
        }

        return true;
    }
}
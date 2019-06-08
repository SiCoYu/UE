// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;
// UE4.22 Log.TraceVerbose 查找不到
using Tools.DotNETCommon;

namespace UnrealBuildTool.Rules
{
	public class ScriptPlugin : ModuleRules
	{
		public ScriptPlugin(ReadOnlyTargetRules Target) : base(Target)
		{
            // 重复定义
            //PublicDefinitions.Add("WITH_LUA=1");
            // error : All source files in module "ScriptPlugin" must include the same precompiled header first.
            // To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to ScriptPlugin.build.cs.
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
				new string[] {					
					//"Programs/UnrealHeaderTool/Public",
					// ... add other public include paths required here ...
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					// ... add other private include paths required here ...
                    "ScriptPlugin/Classes",
                    "ScriptPlugin/Private"
                }
			);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"InputCore",
					"SlateCore",
					// ... add other public dependencies that you statically link with here ...
                    // error LNK2019: unresolved external symbol "__declspec(dllimport) public: static class UClass * __cdecl UClothingSimulationFactory::StaticClass(void)" (__imp_?StaticClass@UClothingSimulationFactory@@SAPEAVUClass@@XZ) referenced in function "int __cdecl SkeletalMeshComponent_Get_ClothingSimulationFactory(struct lua_State *)" (?SkeletalMeshComponent_Get_ClothingSimulationFactory@@YAHPEAUlua_State@@@Z)
                    "ClothingSystemRuntimeInterface",
                }
			);

			if (Target.bBuildEditor == true)
			{
				PublicDependencyModuleNames.AddRange(
					new string[] 
					{
						"UnrealEd", 
					}
				);
			}

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
			);

            //var LuaPath = Path.Combine("..", "Plugins", "ScriptPlugin", "Source", "Lua");				
            //var LuaLibDirectory = Path.Combine(LuaPath, "Lib", Target.Platform.ToString(), "Release");
            //var LuaLibPath = Path.Combine(LuaLibDirectory, "Lua.lib");
            //if (File.Exists(LuaLibPath))
            //{					
            //	PublicDefinitions.Add("WITH_LUA=1");

            //	// Path to Lua include files
            //	var IncludePath = Path.GetFullPath(Path.Combine(LuaPath, "Include"));
            //	PrivateIncludePaths.Add(IncludePath);

            //	// Lib file
            //	PublicLibraryPaths.Add(LuaLibDirectory);
            //	PublicAdditionalLibraries.Add(LuaLibPath);

            //	Log.TraceVerbose("LUA Integration enabled: {0}", IncludePath);
            //}
            //else
            //{
            //	Log.TraceVerbose("LUA Integration NOT enabled");
            //	PublicDefinitions.Add("WITH_LUA=0");
            //}

            string IncludePath = Path.Combine(this.getMyProjectThirdPartyPath(), "Inc", "Lua");
            PublicDefinitions.Add("WITH_LUA=1");
            Log.TraceVerbose("LUA Integration enabled: {0}", IncludePath);

            this.loadThirdPartyInc();
            //LoadLua(Target);
            this.loadThirdLib(Target, "Lua");
        }

        protected string getMyModulePath()
        {
            // “UnrealBuildTool.RulesCompiler.GetModuleFilename(string)”已过时:“GetModuleFilename is deprecated, use the ModuleDirectory property on any ModuleRules instead to get a path to your module.”
            //return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
            //return Path.GetDirectoryName(ModuleDirectory);    // 不是这样获取
            return ModuleDirectory;      // 参照 Engine\Plugins\Runtime\Nvidia\Ansel\Source\Ansel\Ansel.Build.cs 实现
        }

        protected string getMyProjectThirdPartyPath()
        {
            string ret = "";

            ret = Path.GetFullPath(Path.Combine(this.getMyModulePath(), "../../../..", "ThirdParty"));

            return ret;
        }

        private void loadThirdPartyInc()
        {
            PublicIncludePaths.AddRange(
                new string[]
                {
                    // ... add public include paths required here ...
                    Path.Combine(this.getMyProjectThirdPartyPath(), "Inc", "Lua"),
                }
            );
        }

        //private bool LoadLua(ReadOnlyTargetRules Target)
        //{
        //    if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        //    {
        //        string LibrariesPath;
        //        LibrariesPath = Path.Combine(this.getMyProjectThirdPartyPath(), "Lib", "Lua", "Lua_d.lib");
        //        PublicAdditionalLibraries.Add(LibrariesPath);
        //    }
        //    else if (Target.Platform == UnrealTargetPlatform.Android)
        //    {
        //        // UE4.19.1 error CS0122: “UnrealBuildTool.BuildConfiguration”不可访问，因为它受保护级别限制
        //        //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
        //        string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

        //        // UE4.19.1 warning CS0618: “UnrealBuildTool.ModuleRules.ReceiptPropertyList.Add(UnrealBuildTool.ReceiptProperty)”已过时:“Constructing a ReceiptProperty object is deprecated. Call RuntimeDependencies.Add() with the path to the file to stage.”
        //        //AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));
        //        RuntimeDependencies.Add(Path.Combine(BuildPath, "My_APL_armv7.xml"));

        //        PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLua.so");
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
}

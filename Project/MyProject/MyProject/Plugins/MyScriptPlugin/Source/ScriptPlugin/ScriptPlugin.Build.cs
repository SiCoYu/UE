// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

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

            string IncludePath = Path.Combine(ThirdPartyPath, "Inc", "Lua");
            PublicDefinitions.Add("WITH_LUA=1");
            Log.TraceVerbose("LUA Integration enabled: {0}", IncludePath);

            loadThirdPartyInclude();
            LoadLua(Target);
        }

        protected string ModulePath
        {
            get
            {
                // “UnrealBuildTool.RulesCompiler.GetModuleFilename(string)”已过时:“GetModuleFilename is deprecated, use the ModuleDirectory property on any ModuleRules instead to get a path to your module.”
                //return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
                //return Path.GetDirectoryName(ModuleDirectory);    // 不是这样获取
                return ModuleDirectory;      // 参照 Engine\Plugins\Runtime\Nvidia\Ansel\Source\Ansel\Ansel.Build.cs 实现
            }
        }

        protected string ThirdPartyPath
        {
            get
            {
                return Path.GetFullPath(Path.Combine(ModulePath, "../../../..", "ThirdParty"));
            }
        }

        private void loadThirdPartyInclude()
        {
            PublicIncludePaths.AddRange(
                new string[]
                {
                    // ... add public include paths required here ...
                    Path.Combine(ThirdPartyPath, "Inc", "Lua"),
                }
            );
        }

        private bool LoadLua(ReadOnlyTargetRules Target)
        {
            if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
            {
                string LibrariesPath;
                LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Lua", "Lua_d.lib");
                PublicAdditionalLibraries.Add(LibrariesPath);
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                // UE4.19.1 error CS0122: “UnrealBuildTool.BuildConfiguration”不可访问，因为它受保护级别限制
                //string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
                string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

                // UE4.19.1 warning CS0618: “UnrealBuildTool.ModuleRules.ReceiptPropertyList.Add(UnrealBuildTool.ReceiptProperty)”已过时:“Constructing a ReceiptProperty object is deprecated. Call RuntimeDependencies.Add() with the path to the file to stage.”
                //AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));
                RuntimeDependencies.Add(Path.Combine(BuildPath, "My_APL_armv7.xml"));

                PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLua.so");
            }

            return true;
        }
    }
}

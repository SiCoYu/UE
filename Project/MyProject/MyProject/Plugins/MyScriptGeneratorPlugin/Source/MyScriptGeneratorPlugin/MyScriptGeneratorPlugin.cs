// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    /**
     * @note An Introduction to UE4 Plugins
     * @url https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins
	 * UE4引擎自定义插件导出类定义的简单流程
	 * https://blog.csdn.net/albertsh/article/details/73512880
	 * 今天学习了一下使用UE4引擎导出类定义的流程，目的是使用将C++代码导出到Lua文件中，方便C++和Lua代码相互调用，跟踪了一下代码发现，产生Lua可用的C++函数的启动代码实际上在UnrealHeaderTool工具中，原来和生成XXX..generated.h的工具是同一个，如果UnrealHeaderTool工具检测到已经加载的插件继承了IScriptGeneratorPluginInterface，那么它就会调用该插件的ExportClass方法，按照规定的方式将C++定义导出成Lua可用的全局函数
	 */
    public class MyScriptGeneratorPlugin : ModuleRules
	{
		public MyScriptGeneratorPlugin(ReadOnlyTargetRules Target) : base(Target)
		{
            // error : All source files in module "ScriptPlugin" must include the same precompiled header first.
            // To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyScriptGeneratorPlugin.build.cs.
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
				new string[] {					
					"Programs/UnrealHeaderTool/Public",
					// ... add other public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Developer/ScriptGeneratorPlugin/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
					"Projects",
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
}

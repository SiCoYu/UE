// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

/**
 * @brief 自己手工拷贝已经有的插件，然后改名字为 MyScriptGeneratorPlugin ，编译总是报错，说找不到插件 MyScriptGeneratorPlugin ，然后自己通过 UE4Editor -- Editor -- Plugins -- 创建一个同样名字的插件，然后将原来的 MyScriptGeneratorPlugin 内容拷贝过来，结果就编译通过了，奇怪啊
 */
public class MyScriptGeneratorPlugin : ModuleRules
{
	public MyScriptGeneratorPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"MyScriptGeneratorPlugin/Public",
                "Programs/UnrealHeaderTool/Public",     // IScriptGeneratorPluginInterface
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"MyScriptGeneratorPlugin/Private",
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
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Projects",
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

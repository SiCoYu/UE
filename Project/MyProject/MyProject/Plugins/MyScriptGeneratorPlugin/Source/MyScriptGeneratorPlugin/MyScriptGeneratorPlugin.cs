// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    /**
     * @note An Introduction to UE4 Plugins
     * @url https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins
	 * UE4�����Զ����������ඨ��ļ�����
	 * https://blog.csdn.net/albertsh/article/details/73512880
	 * ����ѧϰ��һ��ʹ��UE4���浼���ඨ������̣�Ŀ����ʹ�ý�C++���뵼����Lua�ļ��У�����C++��Lua�����໥���ã�������һ�´��뷢�֣�����Lua���õ�C++��������������ʵ������UnrealHeaderTool�����У�ԭ��������XXX..generated.h�Ĺ�����ͬһ�������UnrealHeaderTool���߼�⵽�Ѿ����صĲ���̳���IScriptGeneratorPluginInterface����ô���ͻ���øò����ExportClass���������չ涨�ķ�ʽ��C++���嵼����Lua���õ�ȫ�ֺ���
	 */
    public class MyScriptGeneratorPlugin : ModuleRules
	{
		public MyScriptGeneratorPlugin(ReadOnlyTargetRules Target) : base(Target)
		{
            // error : All source files in module "ScriptPlugin" must include the same precompiled header first.
            // To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to ScriptGeneratorPlugin.build.cs.
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

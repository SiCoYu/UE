// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

/**
 * @reference https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */
// 终于明白了 MyProjectEditor 在 sln 中是不会被编译的，只有启动 Editor 的时候，才会查找 MyProjectEditor 模块，如果没有才会重新编译，或者 OutExtraModuleNames.Add("MyProjectEditor"); 强制编译
public class MyProjectEditorTarget : TargetRules
{
    //public MyProjectEditorTarget(TargetInfo Target)
    public MyProjectEditorTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Editor;

        // UnrealEngine\Engine\Source\Programs\UnrealBuildTool\System\RulesCompiler.cs
        // public bool bBuildAllPlugins = false;

        // UnrealEngine\Engine\Source\Programs\UnrealBuildTool\Configuration\UEBuildTarget.cs
        // Set the list of plugins that should be built
        //if (Rules.bBuildAllPlugins)
        //{
        //    BuildPlugins = new List<PluginInfo>(ValidPlugins);
        //}
        //else
        //{
        //    BuildPlugins = new List<PluginInfo>(EnabledPlugins);
        //}

        // UnrealEngine\Engine\Source\UE4Editor.Target.cs
        // 奇怪这个设置后，MyProject\Plugins\MyPlugin 才会编译
        bBuildAllPlugins = true;
    }

    //
    // TargetRules interface.
    //

    // Engine\Source\Programs\UnrealBuildTool\System\RulesCompiler.cs
    // <param name="OutExtraModuleNames">Output list of extra modules that this target could utilize</param>
    public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        // 这个字段决定是否编译当前工程，之前写成 "MyProject" ，结果 "MyProjectEditor" 没有编译
        OutExtraModuleNames.Add("MyProject");
        //OutExtraModuleNames.Add("MyProjectEditor");
    }

    public override void SetupGlobalEnvironment(
        TargetInfo Target,
        ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
        ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
        )
    {
        UEBuildConfiguration.bBuildEditor = true;   // 开启是否编辑 MyProjectEditor，但是即使开始，如果不设置文件 MyProject\Source\MyProjectEditor.Target.cs 中的 OutExtraModuleNames.Add("MyProjectEditor"); 也不会编译 MyProjectEditor
    }
}

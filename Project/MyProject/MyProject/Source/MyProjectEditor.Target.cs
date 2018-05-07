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
		this.Type = TargetType.Editor;

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

        /**
         * ue4 plugin的编译加载
         * https://www.cnblogs.com/wellbye/p/5871359.html
         * 另外，在这里也定义该插件是否默认启用【PluginDescriptor.bEnabledByDefault】，如启用的话就会自动包含在任何项目构建中。
         * 而每个项目也可以明确定义了自己需要或屏蔽的插件【ProjectDescriptor.Plugins】，优先级高于前者。
         * 再有就是项目里的每个Target还可以强制指定包含所有插件【TargetRules.bBuildAllPlugins】，优先级又高于前者。比如UE4Editor就强制启用了所有插件。
         * @ file: Engine\Source\Programs\UnrealBuildTool\Configuration\UEBuildTarget.cs
         * @ code: 
         * // Try to add any the other plugins that are valid
		 * if(Rules.bBuildAllPlugins)
         */
        // UnrealEngine\Engine\Source\UE4Editor.Target.cs
        // 奇怪这个设置后，MyProject\Plugins\MyPlugin 才会编译
        this.bBuildAllPlugins = true;

        // warning : SetupBinaries() is deprecated in the 4.16 release. From the constructor in your .target.cs file, use ExtraModuleNames.Add("Foo") to add modules to your target, or set LaunchModuleName = "Foo" to override the name of the launch module for program targets.
        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        // 这个字段决定是否编译当前工程，之前写成 "MyProject" ，结果 "MyProjectEditor" 没有编译
        this.ExtraModuleNames.Add("MyProject"); 	// 如果没有这一行， MyProject 工程不会被编译，只会编译 MyProjectEditor 工程
        this.ExtraModuleNames.Add("MyProjectEditor");
        //OutExtraModuleNames.Add("MyProjectEditor");
    }

    //
    // TargetRules interface.
    //

    // Engine\Source\Programs\UnrealBuildTool\System\RulesCompiler.cs
    // <param name="OutExtraModuleNames">Output list of extra modules that this target could utilize</param>
    // warning : SetupBinaries() is deprecated in the 4.16 release. From the constructor in your .target.cs file, use ExtraModuleNames.Add("Foo") to add modules to your target, or set LaunchModuleName = "Foo" to override the name of the launch module for program targets.
    //   public override void SetupBinaries(
    //	TargetInfo Target,
    //	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
    //	ref List<string> OutExtraModuleNames
    //	)
    //{
    //       // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
    //       // 这个字段决定是否编译当前工程，之前写成 "MyProject" ，结果 "MyProjectEditor" 没有编译
    //       OutExtraModuleNames.Add("MyProject");
    //       //OutExtraModuleNames.Add("MyProjectEditor");
    //   }

    // UE 4.19.1 warning: SetupGlobalEnvironment() has been deprecated in the 4.19 release. Please set options from the constructor instead.
    //public override void SetupGlobalEnvironment(
    //    TargetInfo Target,
    //    ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
    //    ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
    //    )
    //{
    //UEBuildConfiguration.bBuildEditor = true;   // 开启是否编辑 MyProjectEditor，但是即使开始，如果不设置文件 MyProject\Source\MyProjectEditor.Target.cs 中的 OutExtraModuleNames.Add("MyProjectEditor"); 也不会编译 MyProjectEditor

    //if (Target.Platform == UnrealTargetPlatform.Win64)
    //{
    //WindowsPlatform.bUseVCCompilerArgs = true;
    //}
    //}
}

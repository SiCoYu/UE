// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyProjectTarget : TargetRules
{
    //public MyProjectTarget(TargetInfo Target)
    public MyProjectTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
        // 这个字段决定是否编译当前工程，之前写成 "MyProject" ，结果 "MyProjectEditor" 没有编译
        OutExtraModuleNames.Add("MyProject");

        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        if (UEBuildConfiguration.bBuildEditor)
        {
            OutExtraModuleNames.Add("MyProjectEditor");
        }
    }

    public override void SetupGlobalEnvironment(
        TargetInfo Target,
        ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
        ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
        )
    {
        // 4.17 Error
        //OutCPPEnvironmentConfiguration.CLRMode = CPPCLRMode.CLRDisabled;
        //OutCPPEnvironmentConfiguration.bUseRTTI = true;

        //OutCPPEnvironmentConfiguration.bUseStaticCRT = false;

        //OutCPPEnvironmentConfiguration.Target.Configuration = CPPTargetConfiguration.Debug;
        //BuildConfiguration.bDebugBuildsActuallyUseDebugCRT = true;
        UEBuildConfiguration.bBuildEditor = true;   // 开启是否编辑 MyProjectEditor，但是即使开始，如果不设置文件 MyProject\Source\MyProjectEditor.Target.cs 中的 OutExtraModuleNames.Add("MyProjectEditor"); 也不会编译 MyProjectEditor
    }
}

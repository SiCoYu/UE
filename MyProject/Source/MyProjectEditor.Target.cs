// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

/**
 * @reference https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */

public class MyProjectEditorTarget : TargetRules
{
	public MyProjectEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
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
        OutExtraModuleNames.Add("MyProjectEditor");
	}

    public override void SetupGlobalEnvironment(
        TargetInfo Target,
        ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
        ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
        )
    {
        OutCPPEnvironmentConfiguration.CLRMode = CPPCLRMode.CLRDisabled;
        OutCPPEnvironmentConfiguration.bUseRTTI = true;
        //OutCPPEnvironmentConfiguration.bUseStaticCRT = false;

        //OutCPPEnvironmentConfiguration.Target.Configuration = CPPTargetConfiguration.Debug;
        //BuildConfiguration.bDebugBuildsActuallyUseDebugCRT = true;
    }
}

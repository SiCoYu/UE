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
        // ����ֶξ����Ƿ���뵱ǰ���̣�֮ǰд�� "MyProject" ����� "MyProjectEditor" û�б���
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

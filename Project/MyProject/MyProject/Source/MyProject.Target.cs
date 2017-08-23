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
        // ����ֶξ����Ƿ���뵱ǰ���̣�֮ǰд�� "MyProject" ����� "MyProjectEditor" û�б���
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
        UEBuildConfiguration.bBuildEditor = true;   // �����Ƿ�༭ MyProjectEditor�����Ǽ�ʹ��ʼ������������ļ� MyProject\Source\MyProjectEditor.Target.cs �е� OutExtraModuleNames.Add("MyProjectEditor"); Ҳ������� MyProjectEditor
    }
}

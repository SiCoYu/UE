// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyProjectTarget : TargetRules
{
    //public MyProjectTarget(TargetInfo Target)
    public MyProjectTarget(TargetInfo Target) : base(Target)
    {
        // To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
        // PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        this.Type = TargetType.Game;
        // UE4 4.17
        this.bUseStaticCRT = false;

        // warning : SetupBinaries() is deprecated in the 4.16 release. From the constructor in your .target.cs file, use ExtraModuleNames.Add("Foo") to add modules to your target, or set LaunchModuleName = "Foo" to override the name of the launch module for program targets.
        // ����ֶξ����Ƿ���뵱ǰ���̣�֮ǰд�� "MyProject" ����� "MyProjectEditor" û�б���
        ExtraModuleNames.Add("MyProject");
        //ExtraModuleNames.Add("MyProjectEditor");
        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        //if (UEBuildConfiguration.bBuildEditor)
        //{
        //    ExtraModuleNames.Add("MyProjectEditor");
        //}
    }

    //
    // TargetRules interface.
    //
    // warning : SetupBinaries() is deprecated in the 4.16 release. From the constructor in your .target.cs file, use ExtraModuleNames.Add("Foo") to add modules to your target, or set LaunchModuleName = "Foo" to override the name of the launch module for program targets.
 //   public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
 //       // ����ֶξ����Ƿ���뵱ǰ���̣�֮ǰд�� "MyProject" ����� "MyProjectEditor" û�б���
 //       OutExtraModuleNames.Add("MyProject");

 //       // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 //       if (UEBuildConfiguration.bBuildEditor)
 //       {
 //           OutExtraModuleNames.Add("MyProjectEditor");
 //       }
 //   }

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
        //UEBuildConfiguration.bBuildEditor = false;   // �����Ƿ�༭ MyProjectEditor�����Ǽ�ʹ��ʼ������������ļ� MyProject\Source\MyProjectEditor.Target.cs �е� OutExtraModuleNames.Add("MyProjectEditor"); Ҳ������� MyProjectEditor
    }
}

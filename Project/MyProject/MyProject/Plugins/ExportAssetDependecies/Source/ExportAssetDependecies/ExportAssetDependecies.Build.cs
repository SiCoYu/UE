// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExportAssetDependecies : ModuleRules
{
	//public ExportAssetDependecies(TargetInfo Target)
	public ExportAssetDependecies(ReadOnlyTargetRules Target) : base(Target)
	{
		// UE4 4.22  warning : Modules must specify an explicit precompiled header (eg. PrivatePCHHeaderFile = "Public/ExportAssetDependecies.h") from UE 4.21 onwards.
		this.PrivatePCHHeaderFile = "Public/ExportAssetDependeciesPrivatePCH.h";

		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.

		PublicIncludePaths.AddRange(
			new string[] {
				"ExportAssetDependecies/Public"
				// ... add public include paths required here ...
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"ExportAssetDependecies/Private",
				// ... add other private include paths required here ...

				//********** MyProject **********
				// MyProject 尽量包含目录只包含 MyProject/Private 和 MyProject/Public， 这样别的模块如果引用当前模块，就只需要添加包含模块 MyProject，这样就会添加包含目录 MyProject/Private 和 MyProject/Public 引用的模块就不用添加这么多包含目录了 
				// Player 区域
				"../../../Source/MyProject/Private/MyEngine",
				"../../../Source/MyProject/Private/MyEngine/UI/Widgets",
				"../../../Source/MyProject/Private/MyEngine/Persist",
				"../../../Source/MyProject/Private/MyEngine/MyActor",
				"../../../Source/MyProject/Private/MyEngine/Math",
				"../../../Source/MyProject/Private/MyEngine/Misc",
				"../../../Source/MyProject/Private/MyEngine/Network",
				"../../../Source/MyProject/Private/MyEngine/Network/Web",
				"../../../Source/MyProject/Private/MyEngine/MyAsset",
				"../../../Source/MyProject/Private/MyEngine/MyBluePrint",

				"../../../Source/MyProject/Private/MyEngine/MyBase",
				"../../../Source/MyProject/Private/MyEngine/MyBase/Actor",
				"../../../Source/MyProject/Private/MyEngine/MyBase/Frame",
				"../../../Source/MyProject/Private/MyEngine/MyBase/AI",
				"../../../Source/MyProject/Private/MyEngine/MyBase/Anim",
				"../../../Source/MyProject/Private/MyEngine/MyBase/Delegate",
				"../../../Source/MyProject/Private/MyEngine/MyBase/Misc",
				"../../../Source/MyProject/Private/MyEngine/MyBase/HAL",
				"../../../Source/MyProject/Private/MyEngine/MyBase/Tick",

				"../../../Source/MyProject/Private/MyEngine/MyFly",
				"../../../Source/MyProject/Private/MyEngine/MyFly/Actor",
				"../../../Source/MyProject/Private/MyEngine/MyFly/Frame",
				"../../../Source/MyProject/Private/MyEngine/MyFly/AI",
				"../../../Source/MyProject/Private/MyEngine/MyFly/Anim",

				"../../../Source/MyProject/Private/MyEngine/MyTP",
				"../../../Source/MyProject/Private/MyEngine/MyTP/Actor",
				"../../../Source/MyProject/Private/MyEngine/MyTP/Frame",
				"../../../Source/MyProject/Private/MyEngine/MyTP/AI",
				"../../../Source/MyProject/Private/MyEngine/MyTP/Anim",

				"../../../Source/MyProject/Private/MyEngine/MyTom",
				"../../../Source/MyProject/Private/MyEngine/MyTom/Actor",
				"../../../Source/MyProject/Private/MyEngine/MyTom/Frame",
				"../../../Source/MyProject/Private/MyEngine/MyTom/AI",
				"../../../Source/MyProject/Private/MyEngine/MyTom/Anim",

                // Libs 区域
                "../../../Source/MyProject/Private/BaseFrame/Libs/Common",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Common/MiniInc",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Common/ObjectAsset",

				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct/IndexList",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct/KeyIndexList",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct/LinkedList",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList/NoPriorityList",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList/PriorityList",

				"../../../Source/MyProject/Private/BaseFrame/Libs/EngineWrap",
				"../../../Source/MyProject/Private/BaseFrame/Libs/FrameWork",
				"../../../Source/MyProject/Private/BaseFrame/Libs/FrameWork/Layer",
				"../../../Source/MyProject/Private/BaseFrame/Libs/NetWork/Socket",
				"../../../Source/MyProject/Private/BaseFrame/Libs/NetWork/NetCmdDispatch",
				"../../../Source/MyProject/Private/BaseFrame/Libs/NetWork/Web",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Ui/Base",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Ui/Widget",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Ui/Widget/TreeWidget",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Log",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Table",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Table/ItemObject",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Tools",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Input",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Thread",
				"../../../Source/MyProject/Private/BaseFrame/Libs/MySimpleDelegate",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Tools",
				"../../../Source/MyProject/Private/BaseFrame/Libs/DelayHandle",
				"../../../Source/MyProject/Private/BaseFrame/Libs/EventHandle",
				"../../../Source/MyProject/Private/BaseFrame/Libs/FrameHandle",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/ResLoad",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/ResLoad/LoadItem",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/ResLoad/ResourceItem",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/ResLoadData",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/RefAsync",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/InsResMgr",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/InsRes",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/Download",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/DelayTask",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/Version",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Resource/AutoUpdate",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Pool",
				"../../../Source/MyProject/Private/BaseFrame/Libs/MsgRoute",
				"../../../Source/MyProject/Private/BaseFrame/Libs/FileSystem",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Math",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Task",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core/Object",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core/Templates",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core/Rtti",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core/Platform",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core/Memory",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Core/Tools",

				"../../../Source/MyProject/Private/BaseFrame/Libs/LuaBind",
				"../../../Source/MyProject/Private/BaseFrame/Libs/LuaCBridge",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Scene",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Scene/SceneEntityBase",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Auxiliary/AuxLoader",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Auxiliary/AuxUi",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Auxiliary/AuxBase",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Auxiliary/AuxUserData",

				"../../../Source/MyProject/Private/BaseFrame/Libs/Engine",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Engine/HAL",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Engine/MyDelegate",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Engine/Templates",
				"../../../Source/MyProject/Private/BaseFrame/Libs/Misc",

				"../../../Source/MyProject/Private/BaseFrame/App",
				"../../../Source/MyProject/Private/BaseFrame/App/Module/Game",
				"../../../Source/MyProject/Private/BaseFrame/App/Module/Game/EventNotify",
				"../../../Source/MyProject/Private/BaseFrame/App/Module/Game/GameNetHandle",
				"../../../Source/MyProject/Private/BaseFrame/App/Module/Game/RouteMsgHandle",

				"../../../Source/MyProject/Private/BaseFrame/App/Frame",

				"../../../Source/MyProject/Private/BaseFrame/App/Common/FrameWork",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/ProjectData",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/Scene",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/Scene/SceneState",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/Scene/Being",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/Scene/BeingRender",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/Common",
				"../../../Source/MyProject/Private/BaseFrame/App/Common/Module",

                // UI 区域
                "../../../Source/MyProject/Private/BaseFrame/Ui/UiPack",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiTestCanvas",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiCustomButton",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiLoadStyles",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiChat",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiLog",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiEditText",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiSlateTab",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiSlateStyleSet",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiTestUMG",
				"../../../Source/MyProject/Private/BaseFrame/Ui/UiFunctionBar",

                // Test 区域
                "../../../Source/MyProject/Private/BaseFrame/UnitTest",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestBase",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestUi",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestDownload",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestNetClientBuffer",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestOther",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestLuaBind",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestPak",
				"../../../Source/MyProject/Private/BaseFrame/UnitTest/TestAsset",

                // Example
                "../../../Source/MyProject/Private/BaseFrame/Example/AccessMesh",
				"../../../Source/MyProject/Private/BaseFrame/Example/AnimateVertexPositions",
				"../../../Source/MyProject/Private/BaseFrame/Example/AnimationCppAndBlueprint",
				"../../../Source/MyProject/Private/BaseFrame/Example/AnimNode",

				"../../../Source/MyProject/Private/BaseFrame/Example/AsyncLoad",
				"../../../Source/MyProject/Private/BaseFrame/Example/ClearWidgets",
				"../../../Source/MyProject/Private/BaseFrame/Example/CoordinateMapping",
				"../../../Source/MyProject/Private/BaseFrame/Example/CppAndBlueprint",

				"../../../Source/MyProject/Private/BaseFrame/Example/CustomActorIcon",
				"../../../Source/MyProject/Private/BaseFrame/Example/CustomComponents",
				"../../../Source/MyProject/Private/BaseFrame/Example/DeferAttachToSocket",
				"../../../Source/MyProject/Private/BaseFrame/Example/DelegatesInCppBP",

				"../../../Source/MyProject/Private/BaseFrame/Example/DistanceToCollision",
				"../../../Source/MyProject/Private/BaseFrame/Example/DynamicLoadObject",
				"../../../Source/MyProject/Private/BaseFrame/Example/EnumToString",
				"../../../Source/MyProject/Private/BaseFrame/Example/EventHand",

				"../../../Source/MyProject/Private/BaseFrame/Example/ExtendUserWidget",
				"../../../Source/MyProject/Private/BaseFrame/Example/FileAndPath",
				"../../../Source/MyProject/Private/BaseFrame/Example/InterfaceImpl",
				"../../../Source/MyProject/Private/BaseFrame/Example/LogMacro",

				"../../../Source/MyProject/Private/BaseFrame/Example/ModularPawn",
				"../../../Source/MyProject/Private/BaseFrame/Example/MultiThread",
				"../../../Source/MyProject/Private/BaseFrame/Example/ObjectIterator",
				"../../../Source/MyProject/Private/BaseFrame/Example/ObjectLibraryLoad",

				"../../../Source/MyProject/Private/BaseFrame/Example/RWConfigFile",
				"../../../Source/MyProject/Private/BaseFrame/Example/SubclassAccess",
				"../../../Source/MyProject/Private/BaseFrame/Example/TaskGraphSystem",
				"../../../Source/MyProject/Private/BaseFrame/Example/UmgExtendInCpp",

				"../../../Source/MyProject/Private/BaseFrame/Example/UmgInCpp",
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"MyProject",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Json",
				// ... add private dependencies that you statically link with here ...	
				"MyProject",
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

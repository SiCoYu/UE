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
				"MyProject/Private/MyEngine",
				"MyProject/Private/MyEngine/UI/Widgets",
				"MyProject/Private/MyEngine/Persist",
				"MyProject/Private/MyEngine/MyActor",
				"MyProject/Private/MyEngine/Math",
				"MyProject/Private/MyEngine/Misc",
				"MyProject/Private/MyEngine/Network",
				"MyProject/Private/MyEngine/Network/Web",
				"MyProject/Private/MyEngine/MyAsset",
				"MyProject/Private/MyEngine/MyBluePrint",

				"MyProject/Private/MyEngine/MyBase",
				"MyProject/Private/MyEngine/MyBase/Actor",
				"MyProject/Private/MyEngine/MyBase/Frame",
				"MyProject/Private/MyEngine/MyBase/AI",
				"MyProject/Private/MyEngine/MyBase/Anim",
				"MyProject/Private/MyEngine/MyBase/Delegate",
				"MyProject/Private/MyEngine/MyBase/Misc",
				"MyProject/Private/MyEngine/MyBase/HAL",
				"MyProject/Private/MyEngine/MyBase/Tick",

				"MyProject/Private/MyEngine/MyFly",
				"MyProject/Private/MyEngine/MyFly/Actor",
				"MyProject/Private/MyEngine/MyFly/Frame",
				"MyProject/Private/MyEngine/MyFly/AI",
				"MyProject/Private/MyEngine/MyFly/Anim",

				"MyProject/Private/MyEngine/MyTP",
				"MyProject/Private/MyEngine/MyTP/Actor",
				"MyProject/Private/MyEngine/MyTP/Frame",
				"MyProject/Private/MyEngine/MyTP/AI",
				"MyProject/Private/MyEngine/MyTP/Anim",

				"MyProject/Private/MyEngine/MyTom",
				"MyProject/Private/MyEngine/MyTom/Actor",
				"MyProject/Private/MyEngine/MyTom/Frame",
				"MyProject/Private/MyEngine/MyTom/AI",
				"MyProject/Private/MyEngine/MyTom/Anim",

                // Libs 区域
                "MyProject/Private/BaseFrame/Libs/Common",
				"MyProject/Private/BaseFrame/Libs/Common/MiniInc",
				"MyProject/Private/BaseFrame/Libs/Common/ObjectAsset",

				"MyProject/Private/BaseFrame/Libs/DataStruct",
				"MyProject/Private/BaseFrame/Libs/DataStruct/IndexList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/KeyIndexList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/LinkedList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList/NoPriorityList",
				"MyProject/Private/BaseFrame/Libs/DataStruct/NoOrPriorityList/PriorityList",

				"MyProject/Private/BaseFrame/Libs/EngineWrap",
				"MyProject/Private/BaseFrame/Libs/FrameWork",
				"MyProject/Private/BaseFrame/Libs/FrameWork/Layer",
				"MyProject/Private/BaseFrame/Libs/NetWork/Socket",
				"MyProject/Private/BaseFrame/Libs/NetWork/NetCmdDispatch",
				"MyProject/Private/BaseFrame/Libs/NetWork/Web",

				"MyProject/Private/BaseFrame/Libs/Ui/Base",
				"MyProject/Private/BaseFrame/Libs/Ui/Widget",
				"MyProject/Private/BaseFrame/Libs/Ui/Widget/TreeWidget",

				"MyProject/Private/BaseFrame/Libs/Log",
				"MyProject/Private/BaseFrame/Libs/Table",
				"MyProject/Private/BaseFrame/Libs/Table/ItemObject",
				"MyProject/Private/BaseFrame/Libs/Tools",
				"MyProject/Private/BaseFrame/Libs/Input",

				"MyProject/Private/BaseFrame/Libs/Thread",
				"MyProject/Private/BaseFrame/Libs/MySimpleDelegate",
				"MyProject/Private/BaseFrame/Libs/Tools",
				"MyProject/Private/BaseFrame/Libs/DelayHandle",
				"MyProject/Private/BaseFrame/Libs/EventHandle",
				"MyProject/Private/BaseFrame/Libs/FrameHandle",

				"MyProject/Private/BaseFrame/Libs/Resource/ResLoad",
				"MyProject/Private/BaseFrame/Libs/Resource/ResLoad/LoadItem",
				"MyProject/Private/BaseFrame/Libs/Resource/ResLoad/ResourceItem",
				"MyProject/Private/BaseFrame/Libs/Resource/ResLoadData",
				"MyProject/Private/BaseFrame/Libs/Resource/RefAsync",
				"MyProject/Private/BaseFrame/Libs/Resource/InsResMgr",
				"MyProject/Private/BaseFrame/Libs/Resource/InsRes",
				"MyProject/Private/BaseFrame/Libs/Resource/Download",
				"MyProject/Private/BaseFrame/Libs/Resource/DelayTask",
				"MyProject/Private/BaseFrame/Libs/Resource/Version",
				"MyProject/Private/BaseFrame/Libs/Resource/AutoUpdate",

				"MyProject/Private/BaseFrame/Libs/Pool",
				"MyProject/Private/BaseFrame/Libs/MsgRoute",
				"MyProject/Private/BaseFrame/Libs/FileSystem",
				"MyProject/Private/BaseFrame/Libs/Math",
				"MyProject/Private/BaseFrame/Libs/Task",
				"MyProject/Private/BaseFrame/Libs/Core",
				"MyProject/Private/BaseFrame/Libs/Core/Object",
				"MyProject/Private/BaseFrame/Libs/Core/Templates",
				"MyProject/Private/BaseFrame/Libs/Core/Rtti",
				"MyProject/Private/BaseFrame/Libs/Core/Platform",
				"MyProject/Private/BaseFrame/Libs/Core/Memory",
				"MyProject/Private/BaseFrame/Libs/Core/Tools",

				"MyProject/Private/BaseFrame/Libs/LuaBind",
				"MyProject/Private/BaseFrame/Libs/LuaCBridge",
				"MyProject/Private/BaseFrame/Libs/Scene",
				"MyProject/Private/BaseFrame/Libs/Scene/SceneEntityBase",

				"MyProject/Private/BaseFrame/Libs/Auxiliary/AuxLoader",
				"MyProject/Private/BaseFrame/Libs/Auxiliary/AuxUi",
				"MyProject/Private/BaseFrame/Libs/Auxiliary/AuxBase",
				"MyProject/Private/BaseFrame/Libs/Auxiliary/AuxUserData",

				"MyProject/Private/BaseFrame/Libs/Engine",
				"MyProject/Private/BaseFrame/Libs/Engine/HAL",
				"MyProject/Private/BaseFrame/Libs/Engine/MyDelegate",
				"MyProject/Private/BaseFrame/Libs/Engine/Templates",
				"MyProject/Private/BaseFrame/Libs/Misc",

				"MyProject/Private/BaseFrame/App",
				"MyProject/Private/BaseFrame/App/Module/Game",
				"MyProject/Private/BaseFrame/App/Module/Game/EventNotify",
				"MyProject/Private/BaseFrame/App/Module/Game/GameNetHandle",
				"MyProject/Private/BaseFrame/App/Module/Game/RouteMsgHandle",

				"MyProject/Private/BaseFrame/App/Frame",

				"MyProject/Private/BaseFrame/App/Common/FrameWork",
				"MyProject/Private/BaseFrame/App/Common/ProjectData",
				"MyProject/Private/BaseFrame/App/Common/Scene",
				"MyProject/Private/BaseFrame/App/Common/Scene/SceneState",
				"MyProject/Private/BaseFrame/App/Common/Scene/Being",
				"MyProject/Private/BaseFrame/App/Common/Scene/BeingRender",
				"MyProject/Private/BaseFrame/App/Common/Common",
				"MyProject/Private/BaseFrame/App/Common/Module",

                // UI 区域
                "MyProject/Private/BaseFrame/Ui/UiPack",
				"MyProject/Private/BaseFrame/Ui/UiTestCanvas",
				"MyProject/Private/BaseFrame/Ui/UiCustomButton",
				"MyProject/Private/BaseFrame/Ui/UiLoadStyles",
				"MyProject/Private/BaseFrame/Ui/UiChat",
				"MyProject/Private/BaseFrame/Ui/UiLog",
				"MyProject/Private/BaseFrame/Ui/UiEditText",
				"MyProject/Private/BaseFrame/Ui/UiSlateTab",
				"MyProject/Private/BaseFrame/Ui/UiSlateStyleSet",
				"MyProject/Private/BaseFrame/Ui/UiTestUMG",
				"MyProject/Private/BaseFrame/Ui/UiFunctionBar",

                // Test 区域
                "MyProject/Private/BaseFrame/UnitTest",
				"MyProject/Private/BaseFrame/UnitTest/TestBase",
				"MyProject/Private/BaseFrame/UnitTest/TestUi",
				"MyProject/Private/BaseFrame/UnitTest/TestDownload",
				"MyProject/Private/BaseFrame/UnitTest/TestNetClientBuffer",
				"MyProject/Private/BaseFrame/UnitTest/TestOther",
				"MyProject/Private/BaseFrame/UnitTest/TestLuaBind",
				"MyProject/Private/BaseFrame/UnitTest/TestPak",
				"MyProject/Private/BaseFrame/UnitTest/TestAsset",

                // Example
                "MyProject/Private/BaseFrame/Example/AccessMesh",
				"MyProject/Private/BaseFrame/Example/AnimateVertexPositions",
				"MyProject/Private/BaseFrame/Example/AnimationCppAndBlueprint",
				"MyProject/Private/BaseFrame/Example/AnimNode",

				"MyProject/Private/BaseFrame/Example/AsyncLoad",
				"MyProject/Private/BaseFrame/Example/ClearWidgets",
				"MyProject/Private/BaseFrame/Example/CoordinateMapping",
				"MyProject/Private/BaseFrame/Example/CppAndBlueprint",

				"MyProject/Private/BaseFrame/Example/CustomActorIcon",
				"MyProject/Private/BaseFrame/Example/CustomComponents",
				"MyProject/Private/BaseFrame/Example/DeferAttachToSocket",
				"MyProject/Private/BaseFrame/Example/DelegatesInCppBP",

				"MyProject/Private/BaseFrame/Example/DistanceToCollision",
				"MyProject/Private/BaseFrame/Example/DynamicLoadObject",
				"MyProject/Private/BaseFrame/Example/EnumToString",
				"MyProject/Private/BaseFrame/Example/EventHand",

				"MyProject/Private/BaseFrame/Example/ExtendUserWidget",
				"MyProject/Private/BaseFrame/Example/FileAndPath",
				"MyProject/Private/BaseFrame/Example/InterfaceImpl",
				"MyProject/Private/BaseFrame/Example/LogMacro",

				"MyProject/Private/BaseFrame/Example/ModularPawn",
				"MyProject/Private/BaseFrame/Example/MultiThread",
				"MyProject/Private/BaseFrame/Example/ObjectIterator",
				"MyProject/Private/BaseFrame/Example/ObjectLibraryLoad",

				"MyProject/Private/BaseFrame/Example/RWConfigFile",
				"MyProject/Private/BaseFrame/Example/SubclassAccess",
				"MyProject/Private/BaseFrame/Example/TaskGraphSystem",
				"MyProject/Private/BaseFrame/Example/UmgExtendInCpp",

				"MyProject/Private/BaseFrame/Example/UmgInCpp",
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

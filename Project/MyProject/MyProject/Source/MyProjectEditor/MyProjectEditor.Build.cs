using UnrealBuildTool;
 
public class MyProjectEditor : ModuleRules
{
    //public MyProjectEditor(TargetInfo Target)
    // 4.17
    public MyProjectEditor(ReadOnlyTargetRules Target) : base(Target)
    {
		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
		// UE4 4.17 之前没加这一行，结果总是不能生成 UE4Editor-MyProjectEditor-Win64-Debug.dll ，添加这一行就可以生成 UE4Editor-MyProjectEditor-Win64-Debug.dll 了
        this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // warning CS0618: “UnrealBuildTool.ModuleRules.Definitions”已过时:“The 'Definitions' property has been deprecated. Please use 'PublicDefinitions' instead.”
        //this.Definitions.Add("MY_WITH_EDITOR");
        this.PublicDefinitions.Add("MY_WITH_EDITOR");

        //PrivateIncludePaths.Add("MyProjectEditor/Private");
        PrivateIncludePaths.AddRange(
			new string[] 
            {
                // Main area
                "MyProjectEditor/Private/MyEngine",
                "MyProjectEditor/Private/MyEngine/Animation",
                "MyProjectEditor/Private/MyEngine/MyBase",
                "MyProjectEditor/Private/MyEngine/MyAsset",

                // Example area
                "MyProjectEditor/Private/MyEngine/Example/AnimNode",
                "MyProjectEditor/Private/MyEngine/Example/CppAndBlueprint",

				// BaseFrame
				"MyProjectEditor/Private/BaseFrame/AppEditor/Common/EngineWrap",
				"MyProjectEditor/Private/BaseFrame/AppEditor/Module/Asset/ExportAssetDependecies/Private",
				"MyProjectEditor/Private/BaseFrame/AppEditor/Module/Asset/ExportAssetDependecies/Public",

				// UnitTest
				"MyProjectEditor/Private/BaseFrame/UnitTest/TestAssetGraph",




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
                "MyProject/Private/BasicFrame/Libs/Common",
				"MyProject/Private/BasicFrame/Libs/Common/MiniInc",
				"MyProject/Private/BasicFrame/Libs/Common/ObjectAsset",

				"MyProject/Private/BasicFrame/Libs/DataStruct",
				"MyProject/Private/BasicFrame/Libs/DataStruct/IndexList",
				"MyProject/Private/BasicFrame/Libs/DataStruct/KeyIndexList",
				"MyProject/Private/BasicFrame/Libs/DataStruct/LinkedList",
				"MyProject/Private/BasicFrame/Libs/DataStruct/NoOrPriorityList",
				"MyProject/Private/BasicFrame/Libs/DataStruct/NoOrPriorityList/NoPriorityList",
				"MyProject/Private/BasicFrame/Libs/DataStruct/NoOrPriorityList/PriorityList",

				"MyProject/Private/BasicFrame/Libs/EngineWrap",
				"MyProject/Private/BasicFrame/Libs/FrameWork",
				"MyProject/Private/BasicFrame/Libs/FrameWork/Layer",
				"MyProject/Private/BasicFrame/Libs/NetWork/Socket",
				"MyProject/Private/BasicFrame/Libs/NetWork/NetCmdDispatch",
				"MyProject/Private/BasicFrame/Libs/NetWork/Web",

				"MyProject/Private/BasicFrame/Libs/Ui/Base",
				"MyProject/Private/BasicFrame/Libs/Ui/Widget",
				"MyProject/Private/BasicFrame/Libs/Ui/Widget/TreeWidget",

				"MyProject/Private/BasicFrame/Libs/Log",
				"MyProject/Private/BasicFrame/Libs/Table",
				"MyProject/Private/BasicFrame/Libs/Table/ItemObject",
				"MyProject/Private/BasicFrame/Libs/Tools",
				"MyProject/Private/BasicFrame/Libs/Input",

				"MyProject/Private/BasicFrame/Libs/Thread",
				"MyProject/Private/BasicFrame/Libs/MySimpleDelegate",
				"MyProject/Private/BasicFrame/Libs/Tools",
				"MyProject/Private/BasicFrame/Libs/DelayHandle",
				"MyProject/Private/BasicFrame/Libs/EventHandle",
				"MyProject/Private/BasicFrame/Libs/FrameHandle",

				"MyProject/Private/BasicFrame/Libs/Resource/ResLoad",
				"MyProject/Private/BasicFrame/Libs/Resource/ResLoad/LoadItem",
				"MyProject/Private/BasicFrame/Libs/Resource/ResLoad/ResourceItem",
				"MyProject/Private/BasicFrame/Libs/Resource/ResLoadData",
				"MyProject/Private/BasicFrame/Libs/Resource/RefAsync",
				"MyProject/Private/BasicFrame/Libs/Resource/InsResMgr",
				"MyProject/Private/BasicFrame/Libs/Resource/InsRes",
				"MyProject/Private/BasicFrame/Libs/Resource/Download",
				"MyProject/Private/BasicFrame/Libs/Resource/DelayTask",
				"MyProject/Private/BasicFrame/Libs/Resource/Version",
				"MyProject/Private/BasicFrame/Libs/Resource/AutoUpdate",

				"MyProject/Private/BasicFrame/Libs/Pool",
				"MyProject/Private/BasicFrame/Libs/MsgRoute",
				"MyProject/Private/BasicFrame/Libs/FileSystem",
				"MyProject/Private/BasicFrame/Libs/Math",
				"MyProject/Private/BasicFrame/Libs/Task",
				"MyProject/Private/BasicFrame/Libs/Core",
				"MyProject/Private/BasicFrame/Libs/Core/Object",
				"MyProject/Private/BasicFrame/Libs/Core/Templates",
				"MyProject/Private/BasicFrame/Libs/Core/Rtti",
				"MyProject/Private/BasicFrame/Libs/Core/Platform",
				"MyProject/Private/BasicFrame/Libs/Core/Memory",
				"MyProject/Private/BasicFrame/Libs/Core/Tools",

				"MyProject/Private/BasicFrame/Libs/LuaBind",
				"MyProject/Private/BasicFrame/Libs/LuaCBridge",
				"MyProject/Private/BasicFrame/Libs/Scene",
				"MyProject/Private/BasicFrame/Libs/Scene/SceneEntityBase",

				"MyProject/Private/BasicFrame/Libs/Auxiliary/AuxLoader",
				"MyProject/Private/BasicFrame/Libs/Auxiliary/AuxUi",
				"MyProject/Private/BasicFrame/Libs/Auxiliary/AuxBase",
				"MyProject/Private/BasicFrame/Libs/Auxiliary/AuxUserData",

				"MyProject/Private/BasicFrame/Libs/Engine",
				"MyProject/Private/BasicFrame/Libs/Engine/HAL",
				"MyProject/Private/BasicFrame/Libs/Engine/MyDelegate",
				"MyProject/Private/BasicFrame/Libs/Engine/Templates",
				"MyProject/Private/BasicFrame/Libs/Misc",

				"MyProject/Private/BasicFrame/App",
				"MyProject/Private/BasicFrame/App/Module/Game",
				"MyProject/Private/BasicFrame/App/Module/Game/EventNotify",
				"MyProject/Private/BasicFrame/App/Module/Game/GameNetHandle",
				"MyProject/Private/BasicFrame/App/Module/Game/RouteMsgHandle",

				"MyProject/Private/BasicFrame/App/Frame",

				"MyProject/Private/BasicFrame/App/Common/FrameWork",
				"MyProject/Private/BasicFrame/App/Common/ProjectData",
				"MyProject/Private/BasicFrame/App/Common/Scene",
				"MyProject/Private/BasicFrame/App/Common/Scene/SceneState",
				"MyProject/Private/BasicFrame/App/Common/Scene/Being",
				"MyProject/Private/BasicFrame/App/Common/Scene/BeingRender",
				"MyProject/Private/BasicFrame/App/Common/Common",
				"MyProject/Private/BasicFrame/App/Common/Module",

                // UI 区域
                "MyProject/Private/BasicFrame/Ui/UiPack",
				"MyProject/Private/BasicFrame/Ui/UiTestCanvas",
				"MyProject/Private/BasicFrame/Ui/UiCustomButton",
				"MyProject/Private/BasicFrame/Ui/UiLoadStyles",
				"MyProject/Private/BasicFrame/Ui/UiChat",
				"MyProject/Private/BasicFrame/Ui/UiLog",
				"MyProject/Private/BasicFrame/Ui/UiEditText",
				"MyProject/Private/BasicFrame/Ui/UiSlateTab",
				"MyProject/Private/BasicFrame/Ui/UiSlateStyleSet",
				"MyProject/Private/BasicFrame/Ui/UiTestUMG",
				"MyProject/Private/BasicFrame/Ui/UiFunctionBar",

                // Test 区域
                "MyProject/Private/BasicFrame/UnitTest",
				"MyProject/Private/BasicFrame/UnitTest/TestBase",
				"MyProject/Private/BasicFrame/UnitTest/TestUi",
				"MyProject/Private/BasicFrame/UnitTest/TestDownload",
				"MyProject/Private/BasicFrame/UnitTest/TestNetClientBuffer",
				"MyProject/Private/BasicFrame/UnitTest/TestOther",
				"MyProject/Private/BasicFrame/UnitTest/TestLuaBind",
				"MyProject/Private/BasicFrame/UnitTest/TestPak",
				"MyProject/Private/BasicFrame/UnitTest/TestAsset",

                // Example
                "MyProject/Private/BasicFrame/Example/AccessMesh",
				"MyProject/Private/BasicFrame/Example/AnimateVertexPositions",
				"MyProject/Private/BasicFrame/Example/AnimationCppAndBlueprint",
				"MyProject/Private/BasicFrame/Example/AnimNode",

				"MyProject/Private/BasicFrame/Example/AsyncLoad",
				"MyProject/Private/BasicFrame/Example/ClearWidgets",
				"MyProject/Private/BasicFrame/Example/CoordinateMapping",
				"MyProject/Private/BasicFrame/Example/CppAndBlueprint",

				"MyProject/Private/BasicFrame/Example/CustomActorIcon",
				"MyProject/Private/BasicFrame/Example/CustomComponents",
				"MyProject/Private/BasicFrame/Example/DeferAttachToSocket",
				"MyProject/Private/BasicFrame/Example/DelegatesInCppBP",

				"MyProject/Private/BasicFrame/Example/DistanceToCollision",
				"MyProject/Private/BasicFrame/Example/DynamicLoadObject",
				"MyProject/Private/BasicFrame/Example/EnumToString",
				"MyProject/Private/BasicFrame/Example/EventHand",

				"MyProject/Private/BasicFrame/Example/ExtendUserWidget",
				"MyProject/Private/BasicFrame/Example/FileAndPath",
				"MyProject/Private/BasicFrame/Example/InterfaceImpl",
				"MyProject/Private/BasicFrame/Example/LogMacro",

				"MyProject/Private/BasicFrame/Example/ModularPawn",
				"MyProject/Private/BasicFrame/Example/MultiThread",
				"MyProject/Private/BasicFrame/Example/ObjectIterator",
				"MyProject/Private/BasicFrame/Example/ObjectLibraryLoad",

				"MyProject/Private/BasicFrame/Example/RWConfigFile",
				"MyProject/Private/BasicFrame/Example/SubclassAccess",
				"MyProject/Private/BasicFrame/Example/TaskGraphSystem",
				"MyProject/Private/BasicFrame/Example/UmgExtendInCpp",

				"MyProject/Private/BasicFrame/Example/UmgInCpp",
			}
		);

        PublicIncludePaths.AddRange(
            new string[] 
            {
                "MyProjectEditor/Public/MyEngine"
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",

                "AnimGraph",

                "UnrealEd", // UUnrealEdEngine \ UEditorEngine
                "BlueprintGraph",
                "GraphEditor",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",

                "AnimGraphRuntime",
                "AnimationEditor",
                "GeometryMode",
                "MyProject", 
            }
        );
 
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",

                "UnrealEd", // UUnrealEdEngine \ UEditorEngine
                "BlueprintGraph",
                "AnimGraph",

                "GraphEditor",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",

                "AnimGraphRuntime",
                "GeometryMode",
                "MyProject", 
            }
        );

        // AnimGraphRuntime 模块的包含目录需要这样导入，参考 Engine.Build.cs
       // DynamicallyLoadedModuleNames.Add("AnimGraphRuntime");
        //DynamicallyLoadedModuleNames.AddRange(
        //    new string[] 
        //    {
        //        "AnimGraphRuntime"
        //    }
        //);

        // Engine\Plugins\Editor\SpeedTreeImporter\Source\SpeedTreeImporter\SpeedTreeImporter.Build.cs
        //AddEngineThirdPartyPrivateStaticDependencies(Target, "SpeedTree");

        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        // You'll probably also want to add "MyCodeProject" to the PublicDependencyModuleNames in your MyCodeProjectEditor.Build.cs file, as this will allow your editor module access to your game code.
        //PublicDependencyModuleNames.AddRange(
        //    new string[] 
        //    {
        //        "MyProject"
        //    }
        //);

        //CircularlyReferencedDependentModules.AddRange(
        //    new string[] 
        //    {
        //        "MyProject",
        //    }
        //);
    }
}
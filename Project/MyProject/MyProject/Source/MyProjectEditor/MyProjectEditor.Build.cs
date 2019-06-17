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
				"Json",				// Json
				"JsonUtilities",	// Json
				"XmlParser",		// Xml
				// error LNK2019: unresolved external symbol "__declspec(dllimport) public: static class IPluginManager & __cdecl IPluginManager::Get(void)" (__imp_?Get@IPluginManager@@SAAEAV1@XZ) referenced in function "private: static class TSharedRef<class FSlateStyleSet,0> __cdecl FMyExportAssetDependeciesStyle::Create(void)" (?Create@FMyExportAssetDependeciesStyle@@CA?AV?$TSharedRef@VFSlateStyleSet@@$0A@@@XZ)
				"Projects",
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
				"Json",				// Json
				"JsonUtilities",	// Json
				"XmlParser",		// Xml
				// error LNK2019: unresolved external symbol "__declspec(dllimport) public: static class IPluginManager & __cdecl IPluginManager::Get(void)" (__imp_?Get@IPluginManager@@SAAEAV1@XZ) referenced in function "private: static class TSharedRef<class FSlateStyleSet,0> __cdecl FMyExportAssetDependeciesStyle::Create(void)" (?Create@FMyExportAssetDependeciesStyle@@CA?AV?$TSharedRef@VFSlateStyleSet@@$0A@@@XZ)
				"Projects",
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
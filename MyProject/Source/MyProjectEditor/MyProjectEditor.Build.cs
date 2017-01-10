using UnrealBuildTool;
 
public class MyProjectEditor : ModuleRules
{
    public MyProjectEditor(TargetInfo Target)
    {
        //PrivateIncludePaths.Add("MyProjectEditor/Private");
		PrivateIncludePaths.AddRange(
			new string[] 
            {
                // Main area
                "MyProjectEditor/Private/MyEngine",
                "MyProjectEditor/Private/MyEngine/Animation",

                // Example area
                "MyProjectEditor/Private/MyEngine/AnimNode",
                "MyProjectEditor/Private/MyEngine/Example/CppAndBlueprint"
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

                "UnrealEd",
                "BlueprintGraph",
                "GraphEditor",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",

                "MyProject",
            }
        );
 
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
                "UnrealEd",
                "BlueprintGraph",
                "AnimGraph",
            }
        );

        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        // You'll probably also want to add "MyCodeProject" to the PublicDependencyModuleNames in your MyCodeProjectEditor.Build.cs file, as this will allow your editor module access to your game code.
        PublicDependencyModuleNames.AddRange(
            new string[] 
            {
                "MyProject"
            }
        );
 
        CircularlyReferencedDependentModules.AddRange(
            new string[] 
            {
                "MyProject",
            }
        );
    }
}
using UnrealBuildTool;
 
public class MyProjectEditor : ModuleRules
{
    public MyProjectEditor(TargetInfo Target)
    {
        //PrivateIncludePaths.Add("MyProjectEditor/Private");
		PrivateIncludePaths.AddRange(
			new string[] {
                // Main area
                "MyProjectEditor/Private/MyEngine",
                "MyProjectEditor/Private/MyEngine/Animation",

                // Example area
                "MyProjectEditor/Private/MyEngine/AnimNode",
                "MyProjectEditor/Private/MyEngine/Example/CppAndBlueprint"
            }
		);

        PublicIncludePaths.AddRange(
            new string[] {
                "MyProjectEditor/Public/MyEngine"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", });
 
        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "BlueprintGraph", "AnimGraph", });
 
        PublicDependencyModuleNames.AddRange(
             new string[] {
                    "MyProject"
                }
        );
 
        CircularlyReferencedDependentModules.AddRange(
            new string[] {
                    "MyProject",
                }
        );
    }
}
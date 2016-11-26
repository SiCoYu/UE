using UnrealBuildTool;
 
public class MyProjectEditor : ModuleRules
{
    public MyProjectEditor(TargetInfo Target)
    {
        //PrivateIncludePaths.Add("MyProjectEditor/Private");
		PrivateIncludePaths.AddRange(
			new string[] {
                "MyProjectEditor/Private",
                "MyProjectEditor/Private/Animation"
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
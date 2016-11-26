using UnrealBuildTool;
 
public class MyEditorExtension: ModuleRules
{
    public MyEditorExtension(TargetInfo Target)
    {
 
        PrivateIncludePaths.Add("EditorModule/Private");
 
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", });
 
        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "BlueprintGraph", "AnimGraph", });
 
        PublicDependencyModuleNames.AddRange(
             new string[] {
                    "MyGameName"
                }
        );
 
        CircularlyReferencedDependentModules.AddRange(
            new string[] {
                    "MyGameName",
                }
        );
    }
}
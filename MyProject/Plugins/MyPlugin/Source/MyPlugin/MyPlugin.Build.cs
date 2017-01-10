// Some copyright should be here...

using UnrealBuildTool;
// http://www.cnblogs.com/UnrealEngine4/p/3729720.html
// UnrealEngine\Engine\Plugins\Tests\RuntimeTests 这是一个插件模板，可以从这里拷贝基本插件框架
public class MyPlugin : ModuleRules
{
	public MyPlugin(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[] {
                "MyPlugin/Public"
				// ... add public include paths required here ...
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
                "MyPlugin/Private",
				// ... add other private include paths required here ...
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
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

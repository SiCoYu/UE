using UnrealBuildTool;
using System.IO; //路径获取需要用到IO

/**
 * @brief 需要在 MyProject\MyProject.uproject 工程文件中添加如下，才能编译 Plugin
 "AdditionalPluginDirectories": [
 "/MyProject/Plugins"
 */
// http://www.cnblogs.com/UnrealEngine4/p/3729720.html
// UnrealEngine\Engine\Plugins\Tests\RuntimeTests 这是一个插件模板，可以从这里拷贝基本插件框架
// http://blog.csdn.net/yangxuan0261/article/details/52098104
// https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins
public class MyPlugin : ModuleRules
{
	//public MyPlugin(TargetInfo Target)
	// 4.17
	public MyPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
		//this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// UE4 4.22 warning : Modules must specify an explicit precompiled header (eg. PrivatePCHHeaderFile = "Private/MyPluginPrivatePCH.h") from UE 4.21 onwards.
		this.PrivatePCHHeaderFile = "Private/MyPluginPrivatePCH.h";
		PublicIncludePaths.AddRange( //公有文件搜索路径
            new string[] 
            {
                "MyPlugin/Public"
                // ... add public include paths required here ...
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] 
            {
                "MyPlugin/Private" //私有文件搜索路径
                // ... add other private include paths required here ...
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
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

        //LoadThirdPartyLib(Target); //加载第三方库
    }

	private string ModulePath //当前TestPlugin.Build.cs文件所在的路径
	{
		// error CS0619: “UnrealBuildTool.RulesCompiler.GetModuleFilename(string)”已过时:“GetModuleFilename is deprecated, use the ModuleDirectory property on any ModuleRules instead to get a path to your module.”
		//get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
		get
		{
			return ModuleDirectory;
		}
	}

	private string ThirdPartyPath //这个插件引用的第三方库的目录
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));
		}
	}

	private string MyTestLibPath //第三方库MyTestLib的目录
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ThirdPartyPath, "MyTestLib"));
		}
	}

	public bool LoadThirdPartyLib(TargetInfo Target)
    {
        bool isLibrarySupported = false;
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))//平台判断
        {
            isLibrarySupported = true;
            System.Console.WriteLine("----- isLibrarySupported true");
            string PlatformSubPath = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
            string LibrariesPath = Path.Combine(MyTestLibPath, "Lib");
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, PlatformSubPath, "TestLib.lib"));//加载第三方静态库.lib
        }

        if (isLibrarySupported) //成功加载库的情况下，包含第三方库的头文件
        {
            // Include path
            System.Console.WriteLine("----- PublicIncludePaths.Add true");
            PublicIncludePaths.Add(Path.Combine(MyTestLibPath, "Include"));
        }
        return isLibrarySupported;
    }
}

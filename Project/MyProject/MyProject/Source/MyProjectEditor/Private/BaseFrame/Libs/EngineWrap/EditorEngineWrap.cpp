//#include "MyProjectEditor.h"
#include "EditorEngineWrap.h"

// TODO: Developer
#include "IDesktopPlatform.h"	// Engine\Source\Developer\DesktopPlatform\Public\IDesktopPlatform.h
#include "DesktopPlatformModule.h"	// Engine\Source\Developer\DesktopPlatform\Public\DesktopPlatformModule.h

MY_BEGIN_NAMESPACE(MyNS)

//bool EditorEngineWrap::OpenLauncher(const FOpenLauncherOptions& Options)
//{
//	FString CrashedAppPathUri;
//	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
//	FOpenLauncherOptions OpenOptions(FString::Printf(TEXT("apps/%s"), *CrashedAppPathUri));
//	OpenOptions.bSilent = true;
//	DesktopPlatform->OpenLauncher(OpenOptions);
//}
//
//FString EditorEngineWrap::OpenDirectoryDialog(FString& InitialDir)
//{
//	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
//
//	if (DesktopPlatform)
//	{
//		FString FolderName;
//		const FString Title = LOCTEXT("BrowseForFolderTitle", "Choose a directory to monitor").ToString();
//		const bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr), Title, InitialDir, FolderName);
//
//		if (bFolderSelected)
//		{
//			FolderName /= TEXT("");
//		}
//
//		return FolderName;
//	}
//}

MY_END_NAMESPACE
#include "MyProject.h"
#include "HAL/PlatformFilemanager.h"
#include "TestFileAndPathBPFunctionLibrary.h"

UTestFileAndPathBPFunctionLibrary::UTestFileAndPathBPFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void TestFileAndPathBPFunctionLibrary::CreateDirectory(FString FullPath)
{
	FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*FullPath);
}

//Create Directory, Creating Entire Structure as Necessary
//		so if JoyLevels and Folder1 do not exist in JoyLevels/Folder1/Folder2
//			they will be created so that Folder2 can be created!

//This is my solution for fact that trying to create a directory fails 
//		if its super directories do not exist


//Expects entire directory path, such as:

// C:/Folder1/Folder2/Folder3/NewFolderToMake/

//			Author: Rama


 void TestFileAndPath::CreateDirectoryRecursively(FString FolderToMake)
{
	//FolderToMake is not const so split can be used, and does not damage input

	//Loop Proteciton
	const int32 MAX_LOOP_ITR = 3000; //limit of 3000 directories in the structure

									 // Normalize all / and \ to TEXT("/") and remove any trailing TEXT("/") 
									 //if the character before that is not a TEXT("/") or a colon
	FPaths::NormalizeDirectoryName(FolderToMake);

	//Normalize removes the last "/", but my algorithm wants it
	FolderToMake += "/";

	FString Base;
	FString Left;
	FString Remaining;

	//Split off the Root
	FolderToMake.Split(TEXT("/"), &Base, &Remaining);
	Base += "/"; //add root text to Base

	int32 LoopItr = 0;
	while (Remaining != "" && LoopItr < MAX_LOOP_ITR)
	{
		Remaining.Split(TEXT("/"), &Left, &Remaining);

		//Add to the Base
		Base += Left + FString("/"); //add left and split text to Base

									 //Create Incremental Directory Structure!
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*Base);

		LoopItr++;
	}
}
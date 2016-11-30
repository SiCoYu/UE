#include "MyProject.h"
#include "HAL/FileManager.h"
#include "ShareBPFunctionLibrary.h"

UShareBPFunctionLibrary::UShareBPFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

//Happy Message
FString UShareBPFunctionLibrary::GetHappyMessage()
{
	return FString("Victory! Victory BP Library Works!");
}

bool UShareBPFunctionLibrary::SaveStringTextToFile(
	FString SaveDirectory,
	FString FileName,
	FString SaveText,
	bool AllowOverWriting
) {
	//GFileManager?
	//IFileManager::Get().
	//if (!GFileManager) return false;
	//if (IFileManager::Get()) return false;

	//Dir Exists?
	//if (!GFileManager->DirectoryExists(*SaveDirectory))
	if (!IFileManager::Get().DirectoryExists(*SaveDirectory))
	{
		//create directory if it not exist
		//GFileManager->MakeDirectory(*SaveDirectory);
		IFileManager::Get().MakeDirectory(*SaveDirectory);

		//still could not make directory?
		//if (!GFileManager->DirectoryExists(*SaveDirectory))
		if (!IFileManager::Get().DirectoryExists(*SaveDirectory))
		{
			//Could not make the specified directory
			return false;
			//~~~~~~~~~~~~~~~~~~~~~~
		}
	}

	//get complete file path
	SaveDirectory += "\\";
	SaveDirectory += FileName;

	//No over-writing?
	if (!AllowOverWriting)
	{
		//Check if file exists already
		//if (GFileManager->GetFileAgeSeconds(*SaveDirectory) > 0)
		if (IFileManager::Get().GetFileAgeSeconds(*SaveDirectory) > 0)
		{
			//no overwriting
			return false;
		}
	}

	return FFileHelper::SaveStringToFile(SaveText, *SaveDirectory);
}
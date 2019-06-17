#include "MyProject.h"
#include "MFileStream.h"

MY_BEGIN_NAMESPACE(MyNS)

//string MFileStream::readText(int offset = 0, int count = 0, Encoding encode = null)
//{
//	FString SaveDirectory = FString("C:/Path/To/My/Save/Directory");
//	FString FileName = FString("MyFileName.sav");
//	FString TextToSave = FString("Lorem ipsum");
//	bool AllowOverwriting = false;
//
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//
//	// CreateDirectoryTree returns true if the destination
//	// directory existed prior to call or has been created
//	// during the call.
//	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
//	{
//		// Get absolute file path
//		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;
//
//		// Allow overwriting or file doesn't already exist
//		if (AllowOverwriting || !PlatformFile::FileExists(*AbsoluteFilePath))
//		{
//			FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath);
//		}
//	}
//}
//
//byte[] MFileStream::readByte(int offset = 0, int count = 0)
//{
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//
//	IFileHandle* FileHandle = PlatformFile.OpenRead(*FileName);
//	if (FileHandle)
//	{
//		// Create a pointer to MyInteger
//		int32* IntPointer = &MyInteger;
//		// Reinterpret the pointer for the Read function
//		uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);
//
//		// Read the integer from file into our reinterpret pointer
//		FileHandle->Read(ByteBuffer, sizeof(int32));
//
//		// Because ByteBuffer points directly to MyInteger, it's already been updated at this point
//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Read integer is %d"), MyInteger);
//
//		// Close the file again
//		delete FileHandle;
//	}
//}
//
//void MFileStream::writeText(string text, MEncode gkEncode = MEncode.eUTF8)
//{
//
//}
//
//void MFileStream::writeByte(byte[] bytes, int offset = 0, int count = 0)
//{
//	// One
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//
//	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FileName);
//	if (FileHandle)
//	{
//		// Create our byte buffer
//		uint8* ByteArray = reinterpret_cast<uint8*>(FMemory::Malloc(sizeof(int32));
//
//		// If we were to directly write to the byte buffer, data would likely be lost.
//		// It is better practice to reinterpret the pointer to the byte buffer you want
//		// to write to to the type of the data you want to write.
//		int32 * IntPointer = reinterpret_cast<int32*>(ByteArray);
//
//		// Write the integer to the byte buffer
//		*IntPointer = MyInteger;
//
//		// Write the bytes to the file
//		FileHandle->Write(ByteArray, sizeof(int32));
//
//		// Close the file again
//		delete FileHandle;
//
//		// Free the memory allocated to the byte buffer
//		FMemory::Free(ByteArray);
//	}
//
//	// Two
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//
//	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FileName);
//	if (FileHandle)
//	{
//		int32* IntPointer = &MyInteger;
//		uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);
//
//		// Write the bytes to the file
//		FileHandle->Write(ByteBuffer, sizeof(int32));
//
//		// Close the file again
//		delete FileHandle;
//	}
//
//	// Three
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//
//	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FileName);
//	if (FileHandle)
//	{
//		FString Guid = FString(
//			TEXT("// This file is written to disk\n")
//			TEXT("// GUID = "))
//			+ FGuid::NewGuid().ToString();
//
//		FileHandle->Write((const uint8*)TCHAR_TO_ANSI(*Guid), Guid.Len());
//
//		delete FileHandle;
//	}
//}

MY_END_NAMESPACE
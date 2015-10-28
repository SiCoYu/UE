#include "MyProject.h"
#include "DataAssetLoadItem.h"
#include "ByteBuffer.h"

//UDataAssetLoadItem::UDataAssetLoadItem(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//
//}

void UDataAssetLoadItem::loadFile(const FString& Filename)
{
	// if the file has some data in it, read it in
	if (IFileManager::Get().FileSize(*Filename) >= 0)
	{
		/*FString Text;
		if (FFileHelper::LoadFileToString(Text, *Filename))
		{
			ByteBuffer* fileBU = new ByteBuffer(Text.GetAllocatedSize());
			fileBU->writeBytes(TCHAR_TO_ANSI(Text.GetCharArray().GetData()), 0, Text.GetAllocatedSize());
		}*/

		TArray<uint8> arrayBuffer;
		if (FFileHelper::LoadFileToArray(arrayBuffer, *Filename))
		{
			ByteBuffer* fileBU = new ByteBuffer(arrayBuffer.GetAllocatedSize());
			fileBU->writeBytes((char*)(arrayBuffer.GetData()), 0, arrayBuffer.GetAllocatedSize());
		}
	}
}
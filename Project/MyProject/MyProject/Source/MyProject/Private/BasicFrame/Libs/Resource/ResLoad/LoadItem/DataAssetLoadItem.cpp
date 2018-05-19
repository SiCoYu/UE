#include "MyProject.h"
#include "DataAssetLoadItem.h"
#include "MByteBuffer.h"

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
			MByteBuffer* fileBU = new MByteBuffer(Text.GetAllocatedSize());
			fileBU->writeBytes(TCHAR_TO_ANSI(Text.GetCharArray().GetData()), 0, Text.GetAllocatedSize());
		}*/

		TArray<uint8> arrayBuffer;
		if (FFileHelper::LoadFileToArray(arrayBuffer, *Filename))
		{
			MByteBuffer* fileBU = new MByteBuffer(arrayBuffer.GetAllocatedSize());
			fileBU->writeBytes((char*)(arrayBuffer.GetData()), 0, arrayBuffer.GetAllocatedSize());
		}
	}
}
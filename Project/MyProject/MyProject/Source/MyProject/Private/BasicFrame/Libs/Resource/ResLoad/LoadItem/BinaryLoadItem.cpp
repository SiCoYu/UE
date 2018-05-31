#include "MyProject.h"
#include "BinaryLoadItem.h"
#include "MByteBuffer.h"

MY_BEGIN_NAMESPACE(MyNS)

//UBinaryLoadItem::UBinaryLoadItem(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//
//}

UBinaryLoadItem::UBinaryLoadItem()
{
	
}

UBinaryLoadItem::~UBinaryLoadItem()
{
	
}

void UBinaryLoadItem::loadFile(const FString& Filename)
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
			MByteBuffer* pFileBU = MY_NEW MByteBuffer(arrayBuffer.GetAllocatedSize());
			pFileBU->writeBytes((char*)(arrayBuffer.GetData()), 0, arrayBuffer.GetAllocatedSize());
			MY_DELETE pFileBU;
		}
	}
}

MY_END_NAMESPACE
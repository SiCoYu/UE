#include "PackageOperation.h"
#include "EngineMinimal.h"
#include "AssetRegistryModule.h"

PackageOperation::PackageOperation()
{

}

void PackageOperation::saveOneTexture()
{
	//创建名为PackageName值的包
	//PackageName为FString类型
	FString AssetPath = TEXT("/Game/") + PackageName + TEXT("/");
	AssetPath += TextureName;
	UPackage* Package = ::CreatePackage(NULL, *AssetPath);
	Package->FullyLoad();


	//创建
	UTexture2D* NewTexture = NewObject<UTexture2D>(Package, *TextureName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	NewTexture->AddToRoot();
	NewTexture->PlatformData = new FTexturePlatformData();
	NewTexture->PlatformData->SizeX = TextureWidth;
	NewTexture->PlatformData->SizeY = TextureHeight;
	NewTexture->PlatformData->NumSlices = 1;
	//设置像素格式
	NewTexture->PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;


	//创建一个uint8的数组并取得指针
	//这里需要考虑之前设置的像素格式
	uint8* Pixels = new uint8[TextureWidth * TextureHeight * 4];
	for (int32 y = 0; y < TextureHeight; y++)
	{
		for (int32 x = 0; x < TextureWidth; x++)
		{
			int32 curPixelIndex = ((y * TextureWidth) + x);
			//这里可以设置4个通道的值
			//这里需要考虑像素格式，之前设置了PF_B8G8R8A8，那么这里通道的顺序就是BGRA
			Pixels[4 * curPixelIndex] = 100;
			Pixels[4 * curPixelIndex + 1] = 50;
			Pixels[4 * curPixelIndex + 2] = 20;
			Pixels[4 * curPixelIndex + 3] = 255;
		}
	}
	//创建第一个MipMap
	FTexture2DMipMap* Mip = new FTexture2DMipMap();
	NewTexture->PlatformData->Mips.Add(Mip);
	Mip->SizeX = TextureWidth;
	Mip->SizeY = TextureHeight;

	//锁定Texture让它可以被修改
	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = (uint8*)Mip->BulkData.Realloc(TextureWidth * TextureHeight * 4);
	FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * TextureHeight * TextureWidth * 4);
	Mip->BulkData.Unlock();

	//通过以上步骤，我们完成数据的临时写入
	//执行完以下这两个步骤，编辑器中的asset会显示可以保存的状态（如果是指定Asset来获取UTexture2D的指针的情况下）
	NewTexture->Source.Init(TextureWidth, TextureHeight, 1, 1, ETextureSourceFormat::TSF_BGRA8, Pixels);
	NewTexture->UpdateResource();


	Package->MarkPackageDirty();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistryModule.AssetCreated(NewTexture);
	//通过asset路径获取包中文件名
	FString PackageFileName = FPackageName::LongPackageNameToFilename(AssetPath, FPackageName::GetAssetPackageExtension());
	//进行保存
	bool bSaved = UPackage::SavePackage(Package, NewTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	delete[] Pixels;
}
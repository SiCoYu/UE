#include "PackageOperation.h"
#include "EngineMinimal.h"
#include "AssetRegistryModule.h"

PackageOperation::PackageOperation()
{

}

void PackageOperation::saveOneTexture()
{
	//������ΪPackageNameֵ�İ�
	//PackageNameΪFString����
	FString AssetPath = TEXT("/Game/") + PackageName + TEXT("/");
	AssetPath += TextureName;
	UPackage* Package = ::CreatePackage(NULL, *AssetPath);
	Package->FullyLoad();


	//����
	UTexture2D* NewTexture = NewObject<UTexture2D>(Package, *TextureName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	NewTexture->AddToRoot();
	NewTexture->PlatformData = new FTexturePlatformData();
	NewTexture->PlatformData->SizeX = TextureWidth;
	NewTexture->PlatformData->SizeY = TextureHeight;
	NewTexture->PlatformData->NumSlices = 1;
	//�������ظ�ʽ
	NewTexture->PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;


	//����һ��uint8�����鲢ȡ��ָ��
	//������Ҫ����֮ǰ���õ����ظ�ʽ
	uint8* Pixels = new uint8[TextureWidth * TextureHeight * 4];
	for (int32 y = 0; y < TextureHeight; y++)
	{
		for (int32 x = 0; x < TextureWidth; x++)
		{
			int32 curPixelIndex = ((y * TextureWidth) + x);
			//�����������4��ͨ����ֵ
			//������Ҫ�������ظ�ʽ��֮ǰ������PF_B8G8R8A8����ô����ͨ����˳�����BGRA
			Pixels[4 * curPixelIndex] = 100;
			Pixels[4 * curPixelIndex + 1] = 50;
			Pixels[4 * curPixelIndex + 2] = 20;
			Pixels[4 * curPixelIndex + 3] = 255;
		}
	}
	//������һ��MipMap
	FTexture2DMipMap* Mip = new FTexture2DMipMap();
	NewTexture->PlatformData->Mips.Add(Mip);
	Mip->SizeX = TextureWidth;
	Mip->SizeY = TextureHeight;

	//����Texture�������Ա��޸�
	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = (uint8*)Mip->BulkData.Realloc(TextureWidth * TextureHeight * 4);
	FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * TextureHeight * TextureWidth * 4);
	Mip->BulkData.Unlock();

	//ͨ�����ϲ��裬����������ݵ���ʱд��
	//ִ�����������������裬�༭���е�asset����ʾ���Ա����״̬�������ָ��Asset����ȡUTexture2D��ָ�������£�
	NewTexture->Source.Init(TextureWidth, TextureHeight, 1, 1, ETextureSourceFormat::TSF_BGRA8, Pixels);
	NewTexture->UpdateResource();


	Package->MarkPackageDirty();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistryModule.AssetCreated(NewTexture);
	//ͨ��asset·����ȡ�����ļ���
	FString PackageFileName = FPackageName::LongPackageNameToFilename(AssetPath, FPackageName::GetAssetPackageExtension());
	//���б���
	bool bSaved = UPackage::SavePackage(Package, NewTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	delete[] Pixels;
}
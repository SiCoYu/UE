#include "PackageOperation.h"
#include "EngineMinimal.h"
#include "AssetRegistryModule.h"
#include "Factories/MaterialFactoryNew.h"	// UMaterialFactoryNew
#include "Materials/MaterialExpressionMultiply.h"	// UMaterialExpressionMultiply
#include "Materials/MaterialExpressionAppendVector.h"	// UMaterialExpressionAppendVector
#include "Materials/MaterialExpressionTextureCoordinate.h"	// UMaterialExpressionTextureCoordinate
#include "Materials/MaterialExpressionScalarParameter.h"	// UMaterialExpressionScalarParameter
#include "ComponentReregisterContext.h"	// FGlobalComponentReregisterContext 
#include "Factories/AnimBlueprintFactory.h"	// UAnimBlueprintFactory
#include "Animation/AnimInstance.h"		// UAnimInstance
#include "Animation/AnimBlueprint.h"	// UAnimBlueprint
#include "K2Node_CustomEvent.h"			// UK2Node_CustomEvent

PackageOperation::PackageOperation()
{

}

void PackageOperation::createAndSaveOneTexture()
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

void PackageOperation::createAndSaveOneMaterial()
{
	FString MaterialBaseName = "M_Material";
	FString PackageName = "/Game/";
	PackageName += MaterialBaseName;
	UPackage* Package = CreatePackage(NULL, *PackageName);

	// create an unreal material asset
	auto MaterialFactory = NewObject<UMaterialFactoryNew>();
	UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, *MaterialBaseName, RF_Standalone | RF_Public, NULL, GWarn);
	FAssetRegistryModule::AssetCreated(UnrealMaterial);
	Package->FullyLoad();
	Package->SetDirtyFlag(true);

	// Tiling system
	UMaterialExpressionMultiply* Multiply = NewObject<UMaterialExpressionMultiply>(UnrealMaterial);
	UnrealMaterial->Expressions.Add(Multiply);

	// Diffuse
	FStringAssetReference DiffuseAssetPath("/Game/T_Texture");
	UTexture* DiffuseTexture = Cast<UTexture>(DiffuseAssetPath.TryLoad());
	if (DiffuseTexture)
	{
		// make texture sampler
		UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);
		TextureExpression->Texture = DiffuseTexture;
		TextureExpression->SamplerType = SAMPLERTYPE_Color;
		UnrealMaterial->Expressions.Add(TextureExpression);
		UnrealMaterial->BaseColor.Expression = TextureExpression;

		// Tiling
		TextureExpression->Coordinates.Expression = Multiply;
	}


	// Tiling
	UMaterialExpressionAppendVector* Append = NewObject<UMaterialExpressionAppendVector>(UnrealMaterial);
	UnrealMaterial->Expressions.Add(Append);
	Multiply->B.Expression = Append;
	UMaterialExpressionTextureCoordinate* TexCoords = NewObject<UMaterialExpressionTextureCoordinate>(UnrealMaterial);
	UnrealMaterial->Expressions.Add(TexCoords);
	Multiply->A.Expression = TexCoords;
	UMaterialExpressionScalarParameter* XParam = NewObject<UMaterialExpressionScalarParameter>(UnrealMaterial);
	UMaterialExpressionScalarParameter* YParam = NewObject<UMaterialExpressionScalarParameter>(UnrealMaterial);
	UnrealMaterial->Expressions.Add(XParam);
	UnrealMaterial->Expressions.Add(YParam);
	XParam->ParameterName = "TextureRepeatX";
	XParam->DefaultValue = 1;
	YParam->ParameterName = "TextureRepeatY";
	YParam->DefaultValue = 1;
	Append->A.Expression = XParam;
	Append->B.Expression = YParam;

	// let the material update itself if necessary
	UnrealMaterial->PreEditChange(NULL);
	UnrealMaterial->PostEditChange();

	// make sure that any static meshes, etc using this material will stop using the FMaterialResource of the original
	// material, and will use the new FMaterialResource created when we make a new UMaterial in place
	FGlobalComponentReregisterContext RecreateComponents;
}

void PackageOperation::createAndSaveOneAnimBlueprint_Test()
{
	FString AnimBlueprintName = "M_AnimBlueprint";
	FString PackageName = "/Game/";
	PackageName += AnimBlueprintName;

	UAnimBlueprintFactory* AnimBlueprintFactory = NewObject<UAnimBlueprintFactory>();
	UAnimBlueprint* animBlueprint = AnimBlueprintFactory->FactoryCreateNew(UAnimBlueprint::StaticClass(), nullptr, *AnimBlueprintName, RF_Standalone | RF_Public, NULL, GWarn);

	FAssetRegistryModule::AssetCreated(animBlueprint);

	/**
	 * @ref https://github.com/20tab/UnrealEnginePython/blob/master/Source/UnrealEnginePython/Private/Blueprint/UEPyEdGraph.cpp
	 * @ref http://api.unrealengine.com/INT/API/Editor/BlueprintGraph/UK2Node_CustomEvent/index.html
	 */
	// UEdGraphNode* NodeToAdd = NewObject<UEdGraphNode>();
	// NodeToAdd->ImportCustomProperties
	UK2Node_CustomEvent* NodeToAdd = NewObject<UK2Node_CustomEvent>();

	NodeToAdd->NodePosX = 0;
	NodeToAdd->NodePosY = -400;
	FString ResultString("aaa");
	NodeToAdd->AppendName(ResultString);

	animBlueprint->UbergraphPages[0]->AddNode(NodeToAdd);

	FBPVariableDescription VariableDescription = NewObject<FBPVariableDescription>();
	animBlueprint->NewVariables.Add(VariableDescription)
}
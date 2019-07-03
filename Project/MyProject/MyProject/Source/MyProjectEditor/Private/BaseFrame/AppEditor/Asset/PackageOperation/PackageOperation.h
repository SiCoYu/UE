#pragma once

#include "Containers/UnrealString.h"	// FString

class MYPROJECTEDITOR_API PackageOperation
{
protected:
	FString PackageName;
	FString TextureName;
	int TextureWidth;
	int TextureHeight;

public:
	PackageOperation();
	/**
	 * @ref https://zhuanlan.zhihu.com/p/66890786
	 * @ref https://isaratech.com/
	 * @ref https://isaratech.com/ue4-programmatically-create-a-new-material-and-inner-nodes/
     * @ref https://isaratech.com/save-a-procedurally-generated-texture-as-a-new-asset/
	 */
	void createAndSaveOneTexture();
	/**
	 * @ref https://isaratech.com/ue4-programmatically-create-a-new-material-and-inner-nodes/
	 */
	void createAndSaveOneMaterial();
	/**
	 * @ref https://docs.unrealengine.com/en-US/API/Editor/UnrealEd/Factories/UFactory/FactoryCreateNew/2/index.html
	 * UFactory::FactoryCreateNew()
	 * UBlueprintMacroFactory::FactoryCreateNew()
	 * UBlueprintInterfaceFactory::FactoryCreateNew()
	 * UBlueprintFunctionLibraryFactory::FactoryCreateNew()
	 * UBlueprintFactory::FactoryCreateNew()
	 * UGameplayAbilitiesBlueprintFactory::FactoryCreateNew()
	 * UWidgetBlueprintFactory::FactoryCreateNew()
	 * UAnimBlueprintFactory::FactoryCreateNew()
	 * @brief Python ±à¼­Æ÷µ¼Èë¶¯»­, Creating the AnimationBlueprint
     * @brief UnrealEnginePython/tutorials/YourFirstAutomatedPipeline.md
	 * @ref https://github.com/20tab/UnrealEnginePython/blob/master/tutorials/YourFirstAutomatedPipeline.md
	 */
	void createAndSaveOneAnimBlueprint_Test();
};
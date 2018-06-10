#pragma once

#include "EditorReimportHandler.h"	 // FReimportManager
#include "UObject/Object.h"		// UObject
//#include "MyReimportManager.generated.h"

/**
 * @src Engine\Source\Editor\UnrealEd\Private\Editor.cpp
 * @ref Engine\Source\Editor\StaticMeshEditor\Private\StaticMeshEditor.cpp
 */
//UCLASS()
class MyReimportManager
{
	//GENERATED_BODY()

public:
	//FMyReimportManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	MyReimportManager();
	void OnPostReimport(UObject* InObject, bool bSuccess);
};
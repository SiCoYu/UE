#pragma once

#include "Editor.h"	 // FReimportManager
#include "MyReimportManager.generated.h"

/**
 * @src Engine\Source\Editor\UnrealEd\Private\Editor.cpp
 */
UCLASS()
class FMyReimportManager : public FReimportManager
{
	GENERATED_BODY()

public:
	FMyReimportManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
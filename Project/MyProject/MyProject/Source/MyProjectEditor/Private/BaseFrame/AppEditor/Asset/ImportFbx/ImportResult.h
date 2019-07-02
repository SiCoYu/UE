#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "UObject/NoExportTypes.h"

UENUM(BlueprintType)
enum class EImportResult : uint8
{
	Failure,
	Success,
	Cancelled
};
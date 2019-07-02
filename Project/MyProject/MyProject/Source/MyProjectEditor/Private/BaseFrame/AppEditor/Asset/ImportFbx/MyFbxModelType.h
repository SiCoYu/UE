#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "UObject/NoExportTypes.h"

UENUM(BlueprintType)
enum class EMyFbxModelType : uint8
{
	Unknown,
	Monster,
	MapObject,
	Female,
	Male,
	Ride,
	Sky,
	Weapon,
	NPC,
	SFX,
};
#pragma once

#include "Containers/Array.h"	// TArray
#include "UnrealString.h"	// FString

struct FDependicesInfo
{
	TArray<FString> DependicesInGameContentDir;
	TArray<FString> OtherDependices;
	FString AssetClassString;
};
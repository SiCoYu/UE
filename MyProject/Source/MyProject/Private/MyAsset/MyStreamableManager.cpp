#include "MyProject.h"
#include "Misc/StringAssetReference.h"	// FStringAssetReference
#include "UtilStr.h"
#include "MyStreamableManager.h"

FMyStreamableManager::FMyStreamableManager()
{
	
}

FMyStreamableManager::~FMyStreamableManager()
{
	
}

UObject* FMyStreamableManager::SynchronousLoad(std::string path)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(path));
	return mStreamableManager.SynchronousLoad(assetRef);
}
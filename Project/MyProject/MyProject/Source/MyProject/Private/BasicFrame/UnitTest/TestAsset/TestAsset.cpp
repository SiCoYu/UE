#include "MyProject.h"
#include "TestAsset.h"
#include "MyAssetRegistry.h"
#include "Ctx.h"
#include "UObject/NameTypes.h"	// FName
#include "Containers/Array.h"	// TArray
#include "Misc/AssetRegistryInterface.h"	// EAssetRegistryDependencyType

MY_BEGIN_NAMESPACE(MyNS)

void TestAsset::run()
{
	
}

void TestAsset::_testDep()
{
	TArray<FName> OutDependencies;
	GMyAssetRegistry->GetDependencies(TEXT(""), OutDependencies);
}

void TestAsset::_testGetAssetData()
{

}

MY_END_NAMESPACE
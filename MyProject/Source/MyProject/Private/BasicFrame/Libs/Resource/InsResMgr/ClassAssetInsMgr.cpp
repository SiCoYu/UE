#include "MyProject.h"
#include "ClassAssetInsRes.h"
#include "ClassAssetInsMgr.h"

ClassAssetInsMgr::ClassAssetInsMgr()
{

}

void ClassAssetInsMgr::init()
{

}

void ClassAssetInsMgr::dispose()
{

}

UClass* ClassAssetMgr::getAndSyncLoadClass(std::string path)
{
	this->getAndSyncLoad<ClassAssetRes>(path);
}
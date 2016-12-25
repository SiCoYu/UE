#include "MyProject.h"
#include "ClassAssetRes.h"
#include "ClassAssetMgr.h"

ClassAssetMgr::ClassAssetMgr()
{

}

void ClassAssetMgr::init()
{

}

void ClassAssetMgr::dispose()
{

}

UClass* ClassAssetMgr::getAndSyncLoadClass(std::string path)
{
	this->getAndSyncLoad<ClassAssetRes>(path);
}
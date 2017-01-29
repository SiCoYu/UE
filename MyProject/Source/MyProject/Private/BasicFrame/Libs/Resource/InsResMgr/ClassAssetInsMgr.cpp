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

ClassAssetInsRes* ClassAssetInsMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return this->getAndSyncLoad<ClassAssetInsRes>(path, handle);
}

ClassAssetInsRes* ClassAssetInsMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return this->getAndAsyncLoad<ClassAssetInsRes>(path, handle);
}
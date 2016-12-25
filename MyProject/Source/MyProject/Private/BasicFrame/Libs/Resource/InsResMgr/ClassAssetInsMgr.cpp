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

ClassAssetInsRes* ClassAssetInsMgr::getAndSyncLoadClass(std::string path)
{
	return this->getAndSyncLoad<ClassAssetInsRes>(path);
}
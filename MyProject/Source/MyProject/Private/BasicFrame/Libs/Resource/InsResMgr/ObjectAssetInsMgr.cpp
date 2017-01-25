#include "MyProject.h"
#include "ObjectAssetInsMgr.h"
#include "ObjectAssetInsRes.h"

ObjectAssetInsMgr::ObjectAssetInsMgr()
{

}

void ObjectAssetInsMgr::init()
{

}

void ObjectAssetInsMgr::dispose()
{

}

ObjectAssetInsRes* ObjectAssetInsMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate evtHandle)
{
	return Super::getAndSyncLoad<ObjectAssetInsRes>(path, evtHandle);
}

ObjectAssetInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate evtHandle)
{
	return Super::getAndAsyncLoad<ObjectAssetInsRes>(path, evtHandle);
}
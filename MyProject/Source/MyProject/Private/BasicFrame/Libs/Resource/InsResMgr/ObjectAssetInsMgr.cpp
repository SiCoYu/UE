#include "MyProject.h"
#include "ObjectAssetInsMgr.h"
#include "ObjectAssetResItem.h"

ObjectAssetInsMgr::ObjectAssetInsMgr()
{

}

void ObjectAssetInsMgr::init()
{

}

void ObjectAssetInsMgr::dispose()
{

}

ObjectAssetResItem* ObjectAssetInsMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate evtHandle)
{
	return Super::getAndSyncLoad<ObjectAssetResItem>(path, evtHandle);
}
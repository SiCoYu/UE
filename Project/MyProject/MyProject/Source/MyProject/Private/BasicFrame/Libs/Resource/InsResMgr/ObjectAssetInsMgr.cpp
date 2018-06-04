#include "MyProject.h"
#include "ObjectAssetInsMgr.h"
#include "ObjectAssetInsRes.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ObjectAssetInsMgr, ResInsMgrBase)

ObjectAssetInsMgr::ObjectAssetInsMgr()
{

}

ObjectAssetInsMgr::~ObjectAssetInsMgr()
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

ObjectAssetInsRes* ObjectAssetInsMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate evtHandle)
{
	return Super::getAndAsyncLoad<ObjectAssetInsRes>(path, evtHandle);
}

MY_END_NAMESPACE
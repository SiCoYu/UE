#include "MyProject.h"
#include "MaterialInsResMgr.h"
#include "MatInsRes.h"

MaterialInsResMgr::MaterialInsResMgr()
{

}

MaterialInsRes* MaterialInsResMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndSyncLoad<MaterialInsRes>(path, handle);
}

MaterialInsRes* MaterialInsResMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndAsyncLoad<MaterialInsRes>(path, handle);
}
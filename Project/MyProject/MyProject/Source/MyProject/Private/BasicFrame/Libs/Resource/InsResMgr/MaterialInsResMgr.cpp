#include "MyProject.h"
#include "MaterialInsResMgr.h"
#include "MatInsRes.h"

MaterialInsResMgr::MaterialInsResMgr()
{

}

MaterialInsRes* MaterialInsResMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndSyncLoad<MatInsRes>(path, handle);
}

MaterialInsRes* MaterialInsResMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndAsyncLoad<MatInsRes>(path, handle);
}
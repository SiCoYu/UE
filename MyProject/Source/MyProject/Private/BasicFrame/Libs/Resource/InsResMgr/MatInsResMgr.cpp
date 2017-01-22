#include "MyProject.h"
#include "MatInsResMgr.h"
#include "MatInsRes.h"

MatInsResMgr::MatInsResMgr()
{

}

MatInsRes* MatInsResMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndSyncLoad<MatInsRes>(path, handle);
}

MatInsRes* MatInsResMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndAsyncLoad<MatInsRes>(path, handle);
}
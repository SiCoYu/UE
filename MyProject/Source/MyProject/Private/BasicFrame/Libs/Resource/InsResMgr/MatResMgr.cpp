#include "MyProject.h"
#include "MatResMgr.h"
#include "MatRes.h"

MatResMgr::MatResMgr()
{

}

MatInsRes* MatResMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndSyncLoad<MatInsRes>(path, handle);
}

MatInsRes* MatResMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndAsyncLoad<MatInsRes>(path, handle);
}
#include "MyProject.h"
#include "MaterialInsResMgr.h"
#include "MaterialInsRes.h"

MY_BEGIN_NAMESPACE(MyNS)

MaterialInsResMgr::MaterialInsResMgr()
{

}

MaterialInsRes* MaterialInsResMgr::getAndSyncLoadRes(
	std::string path, 
	EventDispatchDelegate handle,
	EventDispatchDelegate progressHandle,
	ResLoadPriority priority
)
{
	return Super::getAndSyncLoad<MaterialInsRes>(
		path, 
		handle
		);
}

MaterialInsRes* MaterialInsResMgr::getAndAsyncLoadRes(
	std::string path, 
	EventDispatchDelegate handle,
	EventDispatchDelegate progressHandle,
	ResLoadPriority priority
)
{
	return Super::getAndAsyncLoad<MaterialInsRes>(
		path, 
		handle
		);
}

MY_END_NAMESPACE
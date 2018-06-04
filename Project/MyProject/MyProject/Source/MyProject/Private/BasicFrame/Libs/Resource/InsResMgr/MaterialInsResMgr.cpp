#include "MyProject.h"
#include "MaterialInsResMgr.h"
#include "MaterialInsRes.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(MaterialInsResMgr, ResInsMgrBase)

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
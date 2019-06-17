#include "MyProject.h"
#include "ClassAssetInsRes.h"
#include "ClassAssetInsMgr.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ClassAssetInsMgr, ResInsMgrBase)

ClassAssetInsMgr::ClassAssetInsMgr()
{

}

ClassAssetInsMgr::~ClassAssetInsMgr()
{
	
}

void ClassAssetInsMgr::init()
{

}

void ClassAssetInsMgr::dispose()
{

}

ResPackType ClassAssetInsMgr::getResPackType()
{
	return ResPackType::eClassType;
}

ClassAssetInsRes* ClassAssetInsMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return this->getAndSyncLoad<ClassAssetInsRes>(path, handle);
}

ClassAssetInsRes* ClassAssetInsMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return this->getAndAsyncLoad<ClassAssetInsRes>(path, handle);
}

MY_END_NAMESPACE
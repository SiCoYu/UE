#include "MyProject.h"
#include "BuildFactoryBase.h"
#include "GObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(BuildFactoryBase, GObject)

BuildFactoryBase::BuildFactoryBase()
{

}

void BuildFactoryBase::init()
{
	
}

void BuildFactoryBase::dispose()
{
	
}

GObject* BuildFactoryBase::createObject(
	TypeUniqueId typeUniqueId, 
	AssetUniqueId assetUniqueId
)
{
	var ret = nullptr;
	return ret;
}

MY_END_NAMESPACE
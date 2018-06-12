#include "MyProject.h"
#include "ObjectFactory.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ObjectFactory, BuildFactoryBase)

ObjectFactory::ObjectFactory()
{

}

void ObjectFactory::init()
{
	
}

void ObjectFactory::dispose()
{
	
}

GObject* ObjectFactory::createObject(
	TypeUniqueId typeUniqueId,
	AssetUniqueId assetUniqueId
)
{
	var ret = nullptr;
	return ret;
}

MY_END_NAMESPACE
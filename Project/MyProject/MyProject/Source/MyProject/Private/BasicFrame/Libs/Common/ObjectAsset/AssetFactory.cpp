#include "MyProject.h"
#include "AssetFactory.h"
#include "GObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AssetFactory, BuildFactoryBase)

AssetFactory::AssetFactory()
{

}

void AssetFactory::init()
{
	
}

void AssetFactory::dispose()
{
	
}

GObject* AssetFactory::createObject(
	TypeUniqueId typeUniqueId, 
	AssetUniqueId assetUniqueId
)
{
	var ret = nullptr;
	var tmpl = nullptr;

	return ret;
}

MY_END_NAMESPACE
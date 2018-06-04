#include "MyProject.h"
#include "ObjectAssetInsRes.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ObjectAssetInsRes, ObjectAssetInsResBase)

ObjectAssetInsRes::ObjectAssetInsRes()
	: Super()
{
	this->mResPackType = eObjectType;
}

MY_END_NAMESPACE
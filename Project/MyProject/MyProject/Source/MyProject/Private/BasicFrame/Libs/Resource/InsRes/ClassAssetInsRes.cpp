#include "MyProject.h"
#include "ClassAssetInsRes.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ClassAssetInsRes, ObjectAssetInsResBase)

ClassAssetInsRes::ClassAssetInsRes()
	: Super()
{
	this->mResPackType = eClassType;
}

ClassAssetInsRes::~ClassAssetInsRes()
{
	
}

MY_END_NAMESPACE
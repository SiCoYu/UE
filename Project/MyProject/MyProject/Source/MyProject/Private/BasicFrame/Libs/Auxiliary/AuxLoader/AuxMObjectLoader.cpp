#include "MyProject.h"
#include "AuxMObjectLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMObjectLoader, AuxMObjectLoaderBase)

AuxMObjectLoader::AuxMObjectLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
	: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
{
	this->mResPackType = eObjectType;
}

MY_END_NAMESPACE
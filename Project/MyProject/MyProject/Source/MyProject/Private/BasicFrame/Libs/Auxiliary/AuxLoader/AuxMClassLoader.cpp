#include "MyProject.h"
#include "AuxMClassLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMClassLoader, AuxMObjectLoaderBase)

AuxMClassLoader::AuxMClassLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
	: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
{
	this->mResPackType = eClassType;
}

MY_END_NAMESPACE
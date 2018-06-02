#include "MyProject.h"
#include "AuxMClassLoader.h"

MY_BEGIN_NAMESPACE(MyNS)

AuxMClassLoader::AuxMClassLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
	: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
{
	this->mResPackType = eClassType;
}

MY_END_NAMESPACE
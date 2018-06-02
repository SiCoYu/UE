#include "MyProject.h"
#include "AuxMObjectLoader.h"

MY_BEGIN_NAMESPACE(MyNS)

AuxMObjectLoader::AuxMObjectLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
	: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
{
	this->mResPackType = eObjectType;
}

MY_END_NAMESPACE
#include "MyProject.h"
#include "AuxMObjectLoader.h"

namespace MyNS
{
	AuxMObjectLoader::AuxMObjectLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
		: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
	{
		this->mResPackType = eObjectType;
	}
}
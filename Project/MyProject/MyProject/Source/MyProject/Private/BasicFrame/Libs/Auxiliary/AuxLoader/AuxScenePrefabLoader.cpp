#include "MyProject.h"
#include "AuxScenePrefabLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxScenePrefabLoader, AuxMObjectLoader)

AuxScenePrefabLoader::AuxScenePrefabLoader(
	std::string path, 
	bool isNeedInsPrefab, 
	bool isInsNeedCoroutine
)
	: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
{
	this->mResPackType = ResPackType::eObjectType;
}

MY_END_NAMESPACE
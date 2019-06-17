#include "MyProject.h"
#include "AuxScenePrefabLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxScenePrefabLoader, AuxMObjectLoader)

AuxScenePrefabLoader::AuxScenePrefabLoader()
	: Super()
{
	this->mResPackType = ResPackType::eObjectType;
}

MY_END_NAMESPACE
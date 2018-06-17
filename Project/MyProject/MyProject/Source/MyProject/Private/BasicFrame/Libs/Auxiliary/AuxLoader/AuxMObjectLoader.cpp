#include "MyProject.h"
#include "AuxMObjectLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMObjectLoader, AuxMObjectLoaderBase)

AuxMObjectLoader::AuxMObjectLoader()
	: Super()
{
	this->mResPackType = ResPackType::eObjectType;
}

MY_END_NAMESPACE
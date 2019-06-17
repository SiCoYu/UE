#include "MyProject.h"
#include "AuxMClassLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMClassLoader, AuxMObjectLoaderBase)

AuxMClassLoader::AuxMClassLoader()
	: Super()
{
	this->mResPackType = ResPackType::eClassType;
}

MY_END_NAMESPACE
#include "MyProject.h"
#include "GObjectBase.h"
#include "TypeDef.h"
#include "MClassFactory.h"

// Engine\Source\Runtime\CoreUObject\Public\UObject\UObject.h
// warning C4996: 'UObjectHeaderDeprecatedWarning': Including UObject.h has been deprecated. Please include Object.h instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_ROOT_CLASS(GObjectBase)
M_REGISTER_CLASS(GObjectBase)

GObjectBase::GObjectBase()
{
	
}

GObjectBase::~GObjectBase()
{
	
}

// ITickedObject
void GObjectBase::onTick(float delta, TickMode tickMode)
{

}

// IGameModule
void GObjectBase::loadGameScene()
{

}

MY_END_NAMESPACE
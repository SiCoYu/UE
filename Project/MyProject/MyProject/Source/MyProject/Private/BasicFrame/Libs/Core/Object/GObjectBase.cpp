#include "MyProject.h"
#include "GObjectBase.h"
#include "TypeDef.h"
#include "MClassFactory.h"

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

MY_END_NAMESPACE
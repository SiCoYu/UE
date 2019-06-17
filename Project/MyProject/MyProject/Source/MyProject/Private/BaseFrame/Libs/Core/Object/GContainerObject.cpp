#include "MyProject.h"
#include "GContainerObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GContainerObject, GObject)

GContainerObject::GContainerObject()
{
	
}

MY_END_NAMESPACE
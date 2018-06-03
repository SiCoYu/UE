#include "MyProject.h"
#include "NullDelayHandleItem.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(NullDelayHandleItem, GObject)

void NullDelayHandleItem::setClientDispose(bool isDispose)
{

}

bool NullDelayHandleItem::isClientDispose()
{
	return false;
}

MY_END_NAMESPACE
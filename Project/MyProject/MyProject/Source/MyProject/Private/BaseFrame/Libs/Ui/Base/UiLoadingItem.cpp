#include "MyProject.h"
#include "UiLoadingItem.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UiLoadingItem, GObject)

UiLoadingItem::UiLoadingItem()
	: mResPath("")
{

}

MY_END_NAMESPACE
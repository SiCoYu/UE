#include "MyProject.h"
#include "UiAttrItem.h"
#include "UiCanvasId.h"
#include "UiLayerId.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UiAttrItem, GObject)

UiAttrItem::UiAttrItem()
{
	this->mCanvasId = UiCanvasId::eCanvas_100;
	this->mLayerId = UiLayerId::eSecondLayer;
}

void UiAttrItem::init()
{

}

void UiAttrItem::dispose()
{

}

MY_END_NAMESPACE
#include "MyProject.h"
#include "UiAttrItem.h"
#include "UiCanvasId.h"
#include "UiLayerId.h"

MY_BEGIN_NAMESPACE(MyNS)

UiAttrItem::UiAttrItem()
{
	this->mCanvasId = UiCanvasId::eCanvas_100;
	this->mLayerId = UiLayerId::eSecondLayer;
}

MY_END_NAMESPACE
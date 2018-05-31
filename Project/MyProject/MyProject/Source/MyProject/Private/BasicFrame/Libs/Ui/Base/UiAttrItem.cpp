#include "MyProject.h"
#include "UiAttrItem.h"
#include "UiCanvasId.h"
#include "UiLayerId.h"

MY_BEGIN_NAMESPACE(MyNS)

UiAttrItem::UiAttrItem()
{
	this->mCanvasId = eCanvas_100;
	this->mLayerId = eSecondLayer;
}

MY_END_NAMESPACE
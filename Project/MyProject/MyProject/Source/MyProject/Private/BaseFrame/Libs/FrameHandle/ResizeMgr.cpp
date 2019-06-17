#include "MyProject.h"
#include "ResizeMgr.h"
#include "IResizeObject.h"

MY_BEGIN_NAMESPACE(MyNS)

void ResizeMgr::addResizeObject(IResizeObject* obj)
{
	this->mResizeList.add(obj);
}

void ResizeMgr::onResize(int viewWidth, int viewHeight)
{
	for(IResizeObject* resizeObj : this->mResizeList.getList())
	{
		resizeObj->onResize(viewWidth, viewHeight);
	}
}

MY_END_NAMESPACE
#include "MyProject.h"
#include "ResizeMgr.h"

void ResizeMgr::addResizeObject(IResizeObject* obj)
{
	m_ResizeLst.Add(obj);
}

void ResizeMgr::onResize(int viewWidth, int viewHeight)
{
	foreach(IResizeObject resizeObj in m_ResizeLst)
	{
		resizeObj.onResize(viewWidth, viewHeight);
	}
}
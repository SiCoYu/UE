#include "MyProject.h"
#include "ResizeMgr.h"
#include "IResizeObject.h"

void ResizeMgr::addResizeObject(IResizeObject* obj)
{
	m_ResizeLst.Add(obj);
}

void ResizeMgr::onResize(int viewWidth, int viewHeight)
{
	for(IResizeObject* resizeObj : m_ResizeLst.getList())
	{
		resizeObj->onResize(viewWidth, viewHeight);
	}
}
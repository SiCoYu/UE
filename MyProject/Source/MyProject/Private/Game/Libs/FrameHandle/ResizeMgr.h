#ifndef __ResizeMgr_H
#define __ResizeMgr_H

#include "MList.h"
class IResizeObject;

class ResizeMgr
{
protected:
	MList<IResizeObject*> m_ResizeLst;

public:
	void addResizeObject(IResizeObject* obj);
	void onResize(int viewWidth, int viewHeight);
};

#endif
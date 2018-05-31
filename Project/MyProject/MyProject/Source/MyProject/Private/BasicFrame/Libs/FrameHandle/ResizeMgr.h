#ifndef __ResizeMgr_H
#define __ResizeMgr_H

#include "MList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IResizeObject;

class ResizeMgr
{
protected:
	MList<IResizeObject*> mResizeList;

public:
	void addResizeObject(IResizeObject* obj);
	void onResize(int viewWidth, int viewHeight);
};

MY_END_NAMESPACE

#endif
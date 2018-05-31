#ifndef __ResLoadResultNotify_H
#define __ResLoadResultNotify_H

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ResLoadState;
class ResEventDispatch;
class IDispatchObject;

/**
    * @brief 非引用计数资源加载结果通知
    */
class ResLoadResultNotify : public GObject
{
protected:
	ResLoadState* mResLoadState;          // 资源加载状态
    ResEventDispatch* mLoadResEventDispatch;    // 事件分发器

public:
	ResLoadResultNotify();
	virtual ~ResLoadResultNotify();

	ResLoadState* getResLoadState();
	void setResLoadState(ResLoadState* value);
	ResEventDispatch* getLoadResEventDispatch();
	void setLoadResEventDispatch(ResEventDispatch* value);
	void onLoadEventHandle(IDispatchObject* dispObj);
	virtual void copyFrom(ResLoadResultNotify* rhv);
};

MY_END_NAMESPACE

#endif
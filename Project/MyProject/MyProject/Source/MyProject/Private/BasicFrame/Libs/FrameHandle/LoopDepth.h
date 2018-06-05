#pragma once

#include "EventDispatchDelegate.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class CallFuncObjectNoParam;

class LoopDepth : public GObject
{
private:
	int mLoopDepth;         // 是否在循环中，支持多层嵌套，就是循环中再次调用循环
	CallFuncObjectNoParam* mIncHandle;     // 增加处理器
	CallFuncObjectNoParam* mDecHandle;     // 减少处理器
	CallFuncObjectNoParam* mZeroHandle;    // 减少到 0 处理器

public:
	LoopDepth();

	void init();
	void dispose();
	void setIncHandle(EventDispatchDelegate handle);
	void setDecHandle(EventDispatchDelegate handle);
	void setZeroHandle(EventDispatchDelegate handle);
	void _incDepth();
	void _decDepth();
	bool _isInDepth();
};

MY_END_NAMESPACE
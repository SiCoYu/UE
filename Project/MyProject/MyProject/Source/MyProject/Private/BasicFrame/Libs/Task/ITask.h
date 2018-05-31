#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ITask
{
public:
    virtual void runTask() = 0;             // 执行任务
	virtual void handleResult() = 0;        // 处理结果
};

MY_END_NAMESPACE
#pragma once

class ITask
{
    virtual void runTask();             // 执行任务
	virtual void handleResult();        // 处理结果
};
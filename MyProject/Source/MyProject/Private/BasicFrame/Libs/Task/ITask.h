#pragma once

class ITask
{
    virtual void runTask() = 0;             // 执行任务
	virtual void handleResult() = 0;        // 处理结果
};
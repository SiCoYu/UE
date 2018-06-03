#pragma once

#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;

class LoopDepth
{
private:
	int mLoopDepth;         // 是否在循环中，支持多层嵌套，就是循环中再次调用循环
	AddOnceEventDispatch* mIncHandle;     // 增加处理器
	AddOnceEventDispatch* mDecHandle;     // 减少处理器
	AddOnceEventDispatch* mZeroHandle;    // 减少到 0 处理器

public:
	LoopDepth()
    {
        this->mLoopDepth = 0;
    }

    void init()
    {

    }

    void dispose()
    {
        if(nullptr != this->mIncHandle)
        {
            this->mIncHandle.clear();
        }
        if(nullptr != this->mDecHandle)
        {
            this->mDecHandle.clear();
        }
        if (nullptr != this->mZeroHandle)
        {
            this->mZeroHandle.clear();
        }
    }

    void setIncHandle(EventDispatchDelegate handle)
    {
        if(nullptr == this->mIncHandle)
        {
            this->mIncHandle = new AddOnceEventDispatch();
        }

        this->mIncHandle.addEventHandle(handle);
    }

    void setDecHandle(EventDispatchDelegate handle)
    {
        if (nullptr == this->mDecHandle)
        {
            this->mDecHandle = new AddOnceEventDispatch();
        }

        this->mDecHandle.addEventHandle(handle);
    }

    void setZeroHandle(EventDispatchDelegate handle)
    {
        if (nullptr == this->mZeroHandle)
        {
            this->mZeroHandle = new AddOnceEventDispatch();
        }

        this->mZeroHandle.addEventHandle(handle);
    }

    void _incDepth()
    {
        ++this->mLoopDepth;

        if(nullptr != this->mIncHandle)
        {
            this->mIncHandle.dispatchEvent(nullptr);
        }
    }

    void _decDepth()
    {
        --this->mLoopDepth;

        if (nullptr != this->mDecHandle)
        {
            this->mDecHandle.dispatchEvent(nullptr);
        }

        if(0 == this->mLoopDepth)
        {
            if (nullptr != this->mZeroHandle)
            {
                this->mZeroHandle.dispatchEvent(nullptr);
            }
        }

        if(this->mLoopDepth < 0)
        {
            this->mLoopDepth = 0;
            // 错误，不对称
            //LogError("LoopDepth::_decDepth, Error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }
    }

    bool _isInDepth()
    {
        return this->mLoopDepth > 0;
    }
};

MY_END_NAMESPACE
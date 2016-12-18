#ifndef __IDelayHandleItem_H
#define __IDelayHandleItem_H

/**
 * @brief 延迟添加的对象
 */
class IDelayHandleItem
{
public:
	virtual void setClientDispose() = 0;
    virtual bool isClientDispose() = 0;
};

#endif
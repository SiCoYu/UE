#ifndef __DaoJiShiTimer_H
#define __DaoJiShiTimer_H

#include "TimerItemBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 倒计时定时器
 */
class DaoJiShiTimer : public TimerItemBase
{
public:
	virtual void OnTimer(float delta) override;
	virtual void reset() override;
};

MY_END_NAMESPACE

#endif
#ifndef __DaoJiShiTimer_H
#define __DaoJiShiTimer_H

#include "TimerItemBase.h"

/**
 * @brief 倒计时定时器
 */
class DaoJiShiTimer : public TimerItemBase
{
public:
	virtual void OnTimer(float delta) override;
	virtual void reset() override;
};

#endif
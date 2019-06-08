using System;

/**
 * @brief 定时器管理器
 */
namespace SDK.Lib
{
    public class TimerMgr : DelayPriorityHandleMgrBase
    {
        protected MList<TimerItemBase> mTimerList;     // 当前所有的定时器列表

        public TimerMgr()
        {
            this.mTimerList = new MList<TimerItemBase>();
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        protected override void _addObject(IDelayHandleItem delayObject, float priority = 0.0f)
        {
            // 检查当前是否已经在队列中
            if (!this.mTimerList.contains(delayObject as TimerItemBase))
            {
                if (this._isInDepth())
                {
                    base._addObject(delayObject, priority);
                }
                else
                {
                    this.mTimerList.add(delayObject as TimerItemBase);
                }
            }
        }

        protected override void _removeObject(IDelayHandleItem delayObject)
        {
            // 检查当前是否在队列中
            if (this.mTimerList.contains(delayObject as TimerItemBase))
            {
                (delayObject as TimerItemBase).mIsDisposed = true;

                if (this._isInDepth())
                {
                    base._removeObject(delayObject);
                }
                else
                {
                    foreach (TimerItemBase item in this.mTimerList.list())
                    {
                        if (UtilSysLibWrap.isAddressEqual(item, delayObject))
                        {
                            this.mTimerList.remove(item);
                            break;
                        }
                    }
                }
            }
        }

        // 从 Lua 中添加定时器，这种定时器尽量整个定时器周期只与 Lua 通信一次
        public void addTimer(TimerItemBase delayObject, float priority = 0.0f)
        {
            if(!this.mTimerList.contains(delayObject))
            {
                this._addObject(delayObject, priority);
            }
        }

        public void removeTimer(TimerItemBase timer)
        {
            if(this.mTimerList.contains(timer))
            {
                this._removeObject(timer);
            }
        }

        public void advance(float delta)
        {
            this._incDepth();

            foreach (TimerItemBase timerItem in this.mTimerList.list())
            {
                if (!timerItem.isClientDispose())
                {
                    timerItem.OnTimer(delta);
                }

                if (timerItem.mIsDisposed)        // 如果已经结束
                {
                    this._removeObject(timerItem);
                }
            }

            this._decDepth();
        }
    }
}
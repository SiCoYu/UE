/**
 * @brief 定时器管理器
 */
namespace SDK.Lib
{
    public class FrameTimerMgr : DelayPriorityHandleMgrBase
    {
        protected MList<FrameTimerItem> mTimerList;     // 当前所有的定时器列表

        public FrameTimerMgr()
        {
            this.mTimerList = new MList<FrameTimerItem>();
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        override protected void _addObject(IDelayHandleItem delayObject, float priority = 0.0f)
        {
            // 检查当前是否已经在队列中
            if (!this.mTimerList.contains(delayObject as FrameTimerItem))
            {
                if (this._isInDepth())
                {
                    base._addObject(delayObject, priority);
                }
                else
                {
                    this.mTimerList.add(delayObject as FrameTimerItem);
                }
            }
        }

        override protected void _removeObject(IDelayHandleItem delayObject)
        {
            // 检查当前是否在队列中
            if (this.mTimerList.contains(delayObject as FrameTimerItem))
            {
                (delayObject as FrameTimerItem).mIsDisposed = true;

                if (this._isInDepth())
                {
                    base._addObject(delayObject);
                }
                else
                {
                    foreach (FrameTimerItem item in this.mTimerList.list())
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

        public void addFrameTimer(FrameTimerItem timer, float priority = 0.0f)
        {
            this._addObject(timer, priority);
        }

        public void removeFrameTimer(FrameTimerItem timer)
        {
            this._removeObject(timer);
        }

        public void advance(float delta)
        {
            this._incDepth();

            foreach (FrameTimerItem timerItem in this.mTimerList.list())
            {
                if (!timerItem.isClientDispose())
                {
                    timerItem.onFrameTimer();
                }
                if (timerItem.mIsDisposed)
                {
                    this._removeObject(timerItem);
                }
            }

            this._decDepth();
        }
    }
}
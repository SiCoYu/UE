namespace SDK.Lib
{
    /**
     * @brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
     */
    public class DelayPriorityHandleMgrBase : DelayNoOrPriorityHandleMgrBase
    {
        public DelayPriorityHandleMgrBase()
        {
            this.mDeferredAddQueue = new PriorityList();
            this.mDeferredAddQueue.setIsSpeedUpFind(true);
            this.mDeferredDelQueue = new PriorityList();
            this.mDeferredDelQueue.setIsSpeedUpFind(true);
        }

        override public void init()
        {
            base.init();
        }

        override public void dispose()
        {
            if(null != this.mDeferredAddQueue)
            {
                this.mDeferredAddQueue.dispose();
                this.mDeferredAddQueue = null;
            }
            if (null != this.mDeferredDelQueue)
            {
                this.mDeferredDelQueue.dispose();
                this.mDeferredDelQueue = null;
            }

            base.dispose();
        }
    }
}
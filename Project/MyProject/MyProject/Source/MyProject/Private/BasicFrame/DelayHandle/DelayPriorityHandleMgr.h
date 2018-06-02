namespace SDK.Lib
{
    /**
     * @brief 延迟优先级处理管理器
     */
    public class DelayPriorityHandleMgr : DelayNoOrPriorityHandleMgr
    {
        public DelayPriorityHandleMgr()
        {
            this.mDeferredAddQueue = new NoPriorityList();
            this.mDeferredAddQueue.setIsSpeedUpFind(true);
            this.mDeferredDelQueue = new NoPriorityList();
            this.mDeferredDelQueue.setIsSpeedUpFind(true);

            this.mNoOrPriorityList = new PriorityList();
            this.mNoOrPriorityList.setIsSpeedUpFind(true);
            this.mNoOrPriorityList.setIsOpKeepSort(true);
        }

        override public void init()
        {
            base.init();
        }

        override public void dispose()
        {
            if (null != this.mDeferredAddQueue)
            {
                this.mDeferredAddQueue.clear();
                this.mDeferredAddQueue = null;
            }
            if (null != this.mDeferredDelQueue)
            {
                this.mDeferredDelQueue.clear();
                this.mDeferredDelQueue = null;
            }
            if (null != this.mNoOrPriorityList)
            {
                this.mNoOrPriorityList.clear();
                this.mNoOrPriorityList = null;
            }

            base.dispose();
        }

        public void addPriorityObject(INoOrPriorityObject priorityObject, float priority = 0.0f)
        {
            this.addNoOrPriorityObject(priorityObject, priority);
        }

        public void removePriorityObject(ITickedObject tickObj)
        {
            this.removeNoOrPriorityObject(tickObj);
        }
    }
}
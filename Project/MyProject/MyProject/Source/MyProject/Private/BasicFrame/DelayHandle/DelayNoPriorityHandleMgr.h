namespace SDK.Lib
{
    /**
     * @brief 延迟优先级处理管理器
     */
    public class DelayNoPriorityHandleMgr : DelayNoOrPriorityHandleMgr
    {
        public DelayNoPriorityHandleMgr()
        {
            this.mDeferredAddQueue = new NoPriorityList();
            this.mDeferredAddQueue.setIsSpeedUpFind(true);
            this.mDeferredDelQueue = new NoPriorityList();
            this.mDeferredDelQueue.setIsSpeedUpFind(true);

            this.mNoOrPriorityList = new NoPriorityList();
            this.mNoOrPriorityList.setIsSpeedUpFind(true);
        }

        override public void init()
        {
            base.init();
        }

        override public void dispose()
        {
            this.mDeferredAddQueue.clear();
            this.mDeferredAddQueue = null;

            this.mDeferredDelQueue.clear();
            this.mDeferredDelQueue = null;

            this.mNoOrPriorityList.clear();
            this.mNoOrPriorityList = null;

            base.dispose();
        }

        public void addNoPriorityObject(INoOrPriorityObject priorityObject)
        {
            this.addNoOrPriorityObject(priorityObject);
        }

        public void removeNoPriorityObject(ITickedObject tickObj)
        {
            this.removeNoOrPriorityObject(tickObj);
        }
    }
}
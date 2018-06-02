namespace SDK.Lib
{
    /**
     * @brief 延迟优先级处理管理器
     */
    public class DelayNoOrPriorityHandleMgr : DelayNoOrPriorityHandleMgrBase
    {
        protected INoOrPriorityList mNoOrPriorityList;

        public DelayNoOrPriorityHandleMgr()
        {

        }

        override public void init()
        {
            base.init();
        }

        override public void dispose()
        {
            base.dispose();
        }

        public bool isEmpty()
        {
            bool ret = (this.mNoOrPriorityList.count() == 0);
            return ret;
        }

        override protected void _addObject(IDelayHandleItem delayObject, float priority = 0.0f)
        {
            if (null != delayObject)
            {
                if (this._isInDepth())
                {
                    base._addObject(delayObject, priority);
                }
                else
                {
                    if (!this.mNoOrPriorityList.contains(delayObject as INoOrPriorityObject))
                    {
                        this.mNoOrPriorityList.addNoOrPriorityObject(delayObject as INoOrPriorityObject, priority);
                    }
                }
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("DelayPriorityHandleMgr::_addObject, failed", LogTypeId.eLogCommon);
                }
            }
        }

        override protected void _removeObject(IDelayHandleItem delayObject)
        {
            if (null != delayObject)
            {
                if (this._isInDepth())
                {
                    base._removeObject(delayObject);
                }
                else
                {
                    if(this.mNoOrPriorityList.contains(delayObject as INoOrPriorityObject))
                    {
                        this.mNoOrPriorityList.removeNoOrPriorityObject(delayObject as INoOrPriorityObject);
                    }
                }
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("DelayPriorityHandleMgr::_removeObject, failed", LogTypeId.eLogCommon);
                }
            }
        }

        public void addNoOrPriorityObject(INoOrPriorityObject priorityObject, float priority = 0.0f)
        {
            this._addObject(priorityObject as IDelayHandleItem, priority);
        }

        public void removeNoOrPriorityObject(ITickedObject tickObj)
        {
            this._removeObject(tickObj as IDelayHandleItem);
        }
    }
}
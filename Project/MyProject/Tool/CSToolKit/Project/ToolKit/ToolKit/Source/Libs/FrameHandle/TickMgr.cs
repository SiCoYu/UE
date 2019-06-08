namespace SDK.Lib
{
    /**
     * @brief 心跳管理器
     */
    public class TickMgr : TickObjectPriorityMgr
    {
        public TickMgr()
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

        override public void advance(float delta, TickMode tickMode)
        {
            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("TickMgr::Advance");
            }

            base.advance(delta, tickMode);

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("TickMgr::Advance");
            }
        }

        public void addTick(ITickedObject tickObj, float priority = 0.0f)
        {
            this._addObject(tickObj as IDelayHandleItem, priority);
        }

        public void removeTick(ITickedObject tickObj)
        {
            this._removeObject(tickObj as IDelayHandleItem);
        }
    }
}
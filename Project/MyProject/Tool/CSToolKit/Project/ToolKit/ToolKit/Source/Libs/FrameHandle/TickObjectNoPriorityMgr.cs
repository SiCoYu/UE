namespace SDK.Lib
{
    // 每一帧执行的对象管理器
    public class TickObjectNoPriorityMgr : DelayNoPriorityHandleMgr, ITickedObject, INoOrPriorityObject
    {
        public TickObjectNoPriorityMgr()
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

        public void onTick(float delta, TickMode tickMode)
        {
            this._incDepth();

            this._onPreAdvance(delta, tickMode);
            this._onExecAdvance(delta, tickMode);
            this._onPostAdvance(delta, tickMode);

            this._decDepth();
        }

        virtual protected void _onPreAdvance(float delta, TickMode tickMode)
        {

        }

        virtual protected void _onExecAdvance(float delta, TickMode tickMode)
        {
            int idx = 0;
            int count = this.mNoOrPriorityList.count();
            ITickedObject tickObject = null;

            while (idx < count)
            {
                tickObject = this.mNoOrPriorityList.get(idx) as ITickedObject;

                if (null != (tickObject as IDelayHandleItem))
                {
                    if (!(tickObject as IDelayHandleItem).isClientDispose())
                    {
                        tickObject.onTick(delta, tickMode);
                    }
                }
                else
                {
                    if (MacroDef.ENABLE_LOG)
                    {
                        Ctx.msInstance.mLogSys.log("TickObjectNoPriorityMgr::_onExecAdvance, failed", LogTypeId.eLogCommon);
                    }
                }

                ++idx;
            }
        }

        virtual protected void _onPostAdvance(float delta, TickMode tickMode)
        {

        }
    }
}
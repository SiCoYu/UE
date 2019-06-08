namespace SDK.Lib
{
    /**
     * @brief 逻辑心跳管理器
     */
    public class LogicTickMgr : TickMgr
    {
        protected TimeInterval mTimeInterval;

        public LogicTickMgr()
        {
            this.mTimeInterval = new TimeInterval();
        }

        override protected void _onExecAdvance(float delta, TickMode tickMode)
        {
            if(this.mTimeInterval.canExec(delta))
            {
                base._onExecAdvance(delta, tickMode);
            }
        }
    }
}
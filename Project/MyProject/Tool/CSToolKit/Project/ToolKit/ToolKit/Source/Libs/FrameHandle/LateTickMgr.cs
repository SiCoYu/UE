namespace SDK.Lib
{
    /**
     * @brief 对应事件 LateUpdate
     */
    public class LateTickMgr : TickMgr
    {
        public LateTickMgr()
        {

        }

        override protected void _onExecAdvance(float delta, TickMode tickMode)
        {
            base._onExecAdvance(delta, tickMode);
        }
    }
}
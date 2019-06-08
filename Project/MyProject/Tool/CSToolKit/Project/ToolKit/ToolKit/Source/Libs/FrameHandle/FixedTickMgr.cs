namespace SDK.Lib
{
    public class FixedTickMgr : TickMgr
    {
        public FixedTickMgr()
        {

        }

        override protected void _onExecAdvance(float delta, TickMode tickMode)
        {
            base._onExecAdvance(delta, tickMode);
        }
    }
}
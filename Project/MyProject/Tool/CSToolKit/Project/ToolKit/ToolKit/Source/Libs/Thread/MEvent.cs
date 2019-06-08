using System.Threading;

namespace SDK.Lib
{
    /**
     * @同步使用的 Event
     */
    public class MEvent
    {
        private ManualResetEvent mEvent;

        public MEvent(bool initialState)
        {
            this.mEvent = new ManualResetEvent(initialState);
        }

        public void WaitOne()
        {
            this.mEvent.WaitOne();
        }

        public bool Reset()
        {
            return this.mEvent.Reset();
        }

        public bool Set()
        {
            return this.mEvent.Set();
        }
    }
}
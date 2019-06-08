namespace SDK.Lib
{
    /**
     * @brief 系统消息流程，整个系统的消息分发都走这里，仅限单线程
     */
    public class SysMsgRoute : MLockQueue<MsgRouteBase>
    {
        public SysMsgRoute(string name)
            : base(name)
        {

        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        public void pushMsg(MsgRouteBase msg)
        {
            if (msg.isMainThreadImmeHandle())
            {
                if(MThread.isMainThread())
                {
                    Ctx.msInstance.mMsgRouteNotify.handleMsg(msg);
                }
                else
                {
                    this.push(msg);
                }
            }
            else
            {
                this.push(msg);
            }
        }

        public MsgRouteBase popMsg()
        {
            return this.pop();
        }
    }
}
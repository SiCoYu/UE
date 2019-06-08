namespace SDK.Lib
{
    public class TaskQueue : MLockQueue<ITask>
    {
        public TaskThreadPool mTaskThreadPool;

        public TaskQueue(string name)
            : base(name)
        {

        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        public new void push(ITask item)
        {
            base.push(item);

            // 检查是否有线程空闲，如果有就唤醒
            this.mTaskThreadPool.notifyIdleThread();
        }
    }
}
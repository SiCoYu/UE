namespace SDK.Lib
{
    /**
     * @brief 任务线程
     */
    public class TaskThread : MThread
    {
        protected TaskQueue mTaskQueue;
        protected MCondition mCondition;
        protected ITask mCurTask;

        public TaskThread(string name, TaskQueue taskQueue)
            : base(null, null)
        {
            this.mTaskQueue = taskQueue;
            this.mCondition = new MCondition(name);
        }

        /**
         *brief 线程回调函数
         */
        override public void threadHandle()
        {
            while (!this.mIsExitFlag)
            {
                this.mCurTask = this.mTaskQueue.pop();

                if(this.mCurTask != default(ITask))
                {
                    this.mCurTask.runTask();
                }
                else
                {
                    this.mCondition.wait();
                }
            }
        }

        public bool notifySelf()
        {
            if(this.mCondition.getCanEnterWait())
            {
                this.mCondition.notifyAll();
                return true;
            }

            return false;
        }
    }
}
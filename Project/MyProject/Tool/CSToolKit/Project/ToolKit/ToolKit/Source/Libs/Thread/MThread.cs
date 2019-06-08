using System.Threading;

namespace SDK.Lib
{
    /**
     *@brief 基本的线程
     */
    public class MThread
    {
        protected static int msMainThreadID;           // 主线程 id
        protected int mCurThreadID;                    // 当前线程的 id

        // 数据区域
        protected Thread mThread;
        protected System.Action<object> mFunctorAction;
        protected object mParam;           // 参数数据
        protected bool mIsExitFlag;           // 退出标志

        public MThread(System.Action<object> func, object param)
        {
            this.mFunctorAction = func;
            this.mParam = param;
        }

        public void setExitFlag(bool value)
        {
            this.mIsExitFlag = value;
        }

        public void setFunctorAction(System.Action<object> value)
        {
            this.mFunctorAction = value;
        }

        public void setParam(object value)
        {
            this.mParam = value;
        }

        // 函数区域
        /**
         *@brief 开启一个线程
         */
        public void start()
        {
            this.mThread = new Thread(new ThreadStart(threadHandle));
            this.mThread.Priority = ThreadPriority.Lowest;
            //mThread.IsBackground = true;             // 继续作为前台线程
            this.mThread.Start();
        }

        public void join()
        {
            //this.mThread.Interrupt();           // 直接线程终止
            this.mThread.Join();
        }

        /**
         *@brief 线程回调函数
         */
        virtual public void threadHandle()
        {
            this.getCurThreadID();

            if(this.mFunctorAction != null)
            {
                this.mFunctorAction(this.mParam);
            }
        }

        protected void getCurThreadID()
        {
            this.mCurThreadID = Thread.CurrentThread.ManagedThreadId;       // 当前线程的 ID
        }

        public bool isCurThread(int threadID)
        {
            return (this.mCurThreadID == threadID);
        }

        static public void getMainThreadID()
        {
            MThread.msMainThreadID = Thread.CurrentThread.ManagedThreadId;
        }

        static public bool isMainThread()
        {
            return (MThread.msMainThreadID == Thread.CurrentThread.ManagedThreadId);
        }

        static public void needMainThread()
        {
            if (!MThread.isMainThread())
            {
                Ctx.msInstance.mLogSys.error("error: log out in other thread");
                throw new System.Exception("cannot call function in thread");
            }
        }

        static public void Sleep(int millisecondsTimeout)
        {
            Thread.Sleep(millisecondsTimeout);
        }
    }
}
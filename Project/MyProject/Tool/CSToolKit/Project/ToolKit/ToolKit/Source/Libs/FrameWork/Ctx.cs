namespace SDK.Lib
{
    /**
     * @brief 全局数据区
     */
    public class Ctx
    {
        static public Ctx msInstance;

        public Config mConfig;                       // 整体配置文件
        public LogSys mLogSys;                    // 日志系统
        public TickMgr mTickMgr;                  // 心跳管理器，正常 Update
        public FixedTickMgr mFixedTickMgr;        // 固定间隔心跳管理器, FixedUpdate
        public LateTickMgr mLateTickMgr;          // 固定间隔心跳管理器, LateUpdate

        public LogicTickMgr mLogicTickMgr;        // 逻辑心跳管理器
        public ProcessSys mProcessSys;            // 游戏处理系统

        public TimerMgr mTimerMgr;                // 定时器系统
        public FrameTimerMgr mFrameTimerMgr;      // 定时器系统
        public EngineLoop mEngineLoop;            // 引擎循环
        public SysMsgRoute mSysMsgRoute;          // 消息分发
        public MsgRouteNotify mMsgRouteNotify;    // RouteMsg 客户端自己消息流程

        public TaskQueue mTaskQueue;
        public TaskThreadPool mTaskThreadPool;
        public SystemFrameData mSystemFrameData;
        public SystemTimeData mSystemTimeData;

        public GlobalDelegate mGlobalDelegate;
        public UniqueStrIdGen mUniqueStrIdGen;

        public MProfiler mProfiler;
        public SystemEvent mSystemEvent;
        public DebugSys mDebugSys;

        public Ctx()
        {
            
        }

        //public static Ctx instance()
        //{
        //    if (null == Ctx.msInstance)
        //    {
        //        Ctx.msInstance = new Ctx();
        //    }

        //    return Ctx.msInstance;
        //}

        virtual public void init()
        {
            // 预先初始化
            this._preInit();
            // 执行初始化
            this._execInit();
            // 后初始化
            this._postInit();
        }

        virtual protected void _preInit()
        {
            this.mUniqueStrIdGen = new UniqueStrIdGen("FindEvt", 0);
            this.mDebugSys = new DebugSys();

            PlatformDefine.init();      // 初始化平台相关的定义
            UtilByte.checkEndian();     // 检查系统大端小端
            MThread.getMainThreadID();  // 获取主线程 ID

            this.mMsgRouteNotify = new MsgRouteNotify();
            this.mGlobalDelegate = new GlobalDelegate();

            this.mTaskQueue = new TaskQueue("TaskQueue");
            this.mTaskThreadPool = new TaskThreadPool();

            this.mSystemFrameData = new SystemFrameData();
            this.mSystemTimeData = new SystemTimeData();

            this.mConfig = new Config();
            this.mProcessSys = new ProcessSys();

            this.mTickMgr = new TickMgr();
            this.mFixedTickMgr = new FixedTickMgr();
            this.mLateTickMgr = new LateTickMgr();

            this.mTimerMgr = new TimerMgr();
            this.mFrameTimerMgr = new FrameTimerMgr();
            this.mEngineLoop = new EngineLoop();
            this.mLogSys = new LogSys();

            this.mLogicTickMgr = new LogicTickMgr();
            this.mProfiler = new MProfiler();
            this.mSystemEvent = new SystemEvent();
            this.mSysMsgRoute = new SysMsgRoute("");
        }

        virtual protected void _execInit()
        {
            this.mConfig.init();
            this.mProcessSys.init();
            this.mSysMsgRoute.init();

            this.mTaskQueue.init();
            this.mTaskThreadPool.init();
            this.mGlobalDelegate.init();

            this.mTickMgr.init();
            this.mFixedTickMgr.init();
            this.mLateTickMgr.init();

            this.mTaskQueue.mTaskThreadPool = this.mTaskThreadPool;
            this.mTaskThreadPool.initThreadPool(2, this.mTaskQueue);
            
            this.mLogicTickMgr.init();
            this.mProfiler.init();
            this.mSystemEvent.init();

            this.mDebugSys.init();
            this.mEngineLoop.init();
        }

        virtual protected void _postInit()
        {
            this.mLogSys.init();
        }

        virtual public void dispose()
        {
            this._preDispose();
            this._execDispose();
            this._postDispose();
        }

        // 依赖类的释放
        virtual protected void _preDispose()
        {
            
        }

        // 主要是逻辑类的释放
        virtual protected void _execDispose()
        {
            if (null != this.mGlobalDelegate)
            {
                this.mGlobalDelegate.dispose();
                this.mGlobalDelegate = null;
            }
            if (null != this.mLogicTickMgr)
            {
                this.mLogicTickMgr.dispose();
                this.mLogicTickMgr = null;
            }
            if (null != this.mTickMgr)
            {
                this.mTickMgr.dispose();
                this.mTickMgr = null;
            }
            if (null != this.mFixedTickMgr)
            {
                this.mFixedTickMgr.dispose();
                this.mFixedTickMgr = null;
            }
            if (null != this.mLateTickMgr)
            {
                this.mLateTickMgr.dispose();
                this.mLateTickMgr = null;
            }
            
            if (null != this.mProfiler)
            {
                this.mProfiler.dispose();
                this.mProfiler = null;
            }
            if(null != this.mSystemEvent)
            {
                this.mSystemEvent.dispose();
                this.mSystemEvent = null;
            }
            if (null != this.mConfig)
            {
                this.mConfig.dispose();
                this.mConfig = null;
            }
            if(null != this.mEngineLoop)
            {
                this.mEngineLoop.dispose();
                this.mEngineLoop = null;
            }
            if(null != this.mProcessSys)
            {
                this.mProcessSys.dispose();
                this.mProcessSys = null;
            }
            if (null != this.mSysMsgRoute)
            {
                this.mSysMsgRoute.dispose();
                this.mSysMsgRoute = null;
            }
            if (null != this.mTaskQueue)
            {
                this.mTaskQueue.dispose();
                this.mTaskQueue = null;
            }
            if (null != this.mTaskThreadPool)
            {
                this.mTaskThreadPool.dispose();
                this.mTaskThreadPool = null;
            }
        }

        // 主要是工具类的释放
        virtual protected void _postDispose()
        {
            // 关闭日志设备
            if (null != this.mLogSys)
            {
                this.mLogSys.dispose();
                this.mLogSys = null;
            }
        }

        virtual public void run()
        {

        }

        public void quitApp()
        {
            this.dispose();

            // 释放自己
            //msInstance = null;
        }
    }
}
namespace SDK.Lib
{
    public class LogSys
    {
        protected MLockList<string> mAsyncLogList;              // 这个是多线程访问的
        protected MLockList<string> mAsyncWarnList;            // 这个是多线程访问的
        protected MLockList<string> mAsyncErrorList;          // 这个是多线程访问的

        protected string mTmpStr;

        protected MList<LogDeviceBase> mLogDeviceList;
        protected MList<LogTypeId>[] mEnableLogTypeList;

        protected bool[] mEnableLog;    // 全局开关
        protected bool[] mIsOutStack;     // 是否显示堆栈信息
        protected bool[] mIsOutTimeStamp;   // 是否有时间戳

        protected string mFileSuffix;

        // 构造函数仅仅是初始化变量，不涉及逻辑
        public LogSys()
        {
            this.mAsyncLogList = new MLockList<string>("Logger_asyncLogList");
            this.mAsyncWarnList = new MLockList<string>("Logger_asyncWarnList");
            this.mAsyncErrorList = new MLockList<string>("Logger_asyncErrorList");
            this.mLogDeviceList = new MList<LogDeviceBase>();

#if UNITY_5
            Application.logMessageReceived += onDebugLogCallbackHandler;
            Application.logMessageReceivedThreaded += onDebugLogCallbackThreadHandler;
#elif UNITY_4_6 || UNITY_4_5
            Application.RegisterLogCallback(onDebugLogCallbackHandler);
            Application.RegisterLogCallbackThreaded(onDebugLogCallbackThreadHandler);
#endif

            this.mEnableLogTypeList = new MList<LogTypeId>[(int)LogColor.eLC_Count];

            this.mEnableLogTypeList[(int)LogColor.eLC_LOG] = new MList<LogTypeId>();
            this.mEnableLogTypeList[(int)LogColor.eLC_WARN] = new MList<LogTypeId>();
            this.mEnableLogTypeList[(int)LogColor.eLC_ERROR] = new MList<LogTypeId>();

            this.mEnableLog = new bool[(int)LogColor.eLC_Count];
            this.mEnableLog[(int)LogColor.eLC_LOG] = MacroDef.ENABLE_LOG;
            this.mEnableLog[(int)LogColor.eLC_WARN] = MacroDef.ENABLE_WARN;
            this.mEnableLog[(int)LogColor.eLC_ERROR] = MacroDef.ENABLE_ERROR;

            this.mIsOutStack = new bool[(int)LogColor.eLC_Count];
            this.mIsOutStack[(int)LogColor.eLC_LOG] = false;
            this.mIsOutStack[(int)LogColor.eLC_WARN] = false;
            this.mIsOutStack[(int)LogColor.eLC_ERROR] = false;

            this.mIsOutTimeStamp = new bool[(int)LogColor.eLC_Count];
            this.mIsOutTimeStamp[(int)LogColor.eLC_LOG] = false;
            this.mIsOutTimeStamp[(int)LogColor.eLC_WARN] = false;
            this.mIsOutTimeStamp[(int)LogColor.eLC_ERROR] = false;

            this.mFileSuffix = "A1000";

            this.addLogFilter();
            this.addWarnFilter();
            this.addErrorFilter();
        }

        // 初始化逻辑处理
        public void init()
        {
            this.registerDevice();
            this.registerFileLogDevice();
        }

        // 析构
        public void dispose()
        {
            this.closeDevice();
        }

        protected void addLogFilter()
        {
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogCommon);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogResLoader);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogLocalFile);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogTestRL);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogAcceleration);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogUnityCB);

            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogSplitMergeEmit);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogSceneInterActive);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogKBE);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogScene);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogBeingMove);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogEventRemove);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogMusicBug);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogLoadBug);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogMergeBug);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogEatBug);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogSimHitBullet);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogTwoDTerrain);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogPriorityListCheck);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogNoPriorityListCheck);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogPosSyn);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogPlaneError);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogDownload);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogAutoUpdate);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogProfileDebug);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogProfile);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogLoadLua);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogLoadExcel);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogNetwork);
            this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogReconnection);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogDataStruct);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogMusic);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogBeginnerGuide);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogEventHandleToggleError);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogAppBin);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogVoice);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogMoveError);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogPackPieceBug);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogShareRoute);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogPreLoad);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogAutoClear);
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogWinFocus);
            this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogTwoDSceneMgr);

            // 编辑器日志
            //this.mEnableLogTypeList[(int)LogColor.eLC_LOG].add(LogTypeId.eLogEditorBuildPlayer);
        }

        protected void addWarnFilter()
        {

        }

        protected void addErrorFilter()
        {
            //this.mEnableLogTypeList[(int)LogColor.eLC_ERROR].add(LogTypeId.eLogLoadBug);
            this.mEnableLogTypeList[(int)LogColor.eLC_ERROR].add(LogTypeId.eErrorDownload);
        }

        public void setFileSuffix(string value)
        {
            this.mFileSuffix = value;
        }

        public void setEnableLog(bool value)
        {
            this.mEnableLog[(int)LogColor.eLC_LOG] = value;
        }

        public void setEnableWarn(bool value)
        {
            this.mEnableLog[(int)LogColor.eLC_WARN] = value;
        }

        public void setEnableError(bool value)
        {
            this.mEnableLog[(int)LogColor.eLC_ERROR] = value;
        }

        protected void registerDevice()
        {
            LogDeviceBase logDevice = null;

            if (MacroDef.ENABLE_WINLOG)
            {
                logDevice = new WinLogDevice();
                logDevice.initDevice();
                this.mLogDeviceList.add(logDevice);
            }

            if (MacroDef.ENABLE_NETLOG)
            {
                logDevice = new NetLogDevice();
                logDevice.initDevice();
                this.mLogDeviceList.add(logDevice);
            }
        }

        // 注册文件日志，因为需要账号，因此需要等待输入账号后才能注册，可能多次注册
        public void registerFileLogDevice()
        {
            if (MacroDef.ENABLE_FILELOG)
            {
                unRegisterFileLogDevice();

                LogDeviceBase logDevice = null;
                logDevice = new FileLogDevice();
                (logDevice as FileLogDevice).fileSuffix = this.mFileSuffix;
                logDevice.initDevice();
                this.mLogDeviceList.add(logDevice);
            }
        }

        protected void unRegisterFileLogDevice()
        {
            foreach(var item in mLogDeviceList.list())
            {
                if(typeof(FileLogDevice) == item.GetType())
                {
                    item.closeDevice();
                    this.mLogDeviceList.remove(item);
                    break;
                }
            }
        }

        /**
         * @brief 所有的异常日志都走这个接口
         */
        public void catchLog(string message)
        {
            log("Out Catch Log");
            log(message);
        }

        protected bool isInFilter(LogTypeId logTypeId, LogColor logColor)
        {
            bool ret = false;

            if (this.mEnableLog[(int)logColor])
            {
                if (this.mEnableLogTypeList[(int)logColor].contains(logTypeId))
                {
                    ret = true;
                }
            }

            return ret;
        }

        // Lua 调用 Log 这个函数的时候， LogTypeId 类型转换会报错，不能使用枚举类型
        public void lua_log(string message, int logTypeId = 0)
        {
            //this.log(message, (LogTypeId)logTypeId);
            this.logout(string.Format("Lua-{0}", message), LogColor.eLC_LOG);
        }

        public void log(string message, LogTypeId logTypeId = LogTypeId.eLogCommon)
        {
            if (this.isInFilter(logTypeId, LogColor.eLC_LOG))
            {
                if(this.mIsOutTimeStamp[(int)LogColor.eLC_LOG])
                {
                    message = string.Format("{0}: {1}", UtilSysLibWrap.getFormatTime(), message);
                }

                if (this.mIsOutStack[(int)LogColor.eLC_LOG])
                {
                    System.Diagnostics.StackTrace stackTrace = new System.Diagnostics.StackTrace(true);
                    string traceStr = stackTrace.ToString();
                    message = string.Format("{0}\n{1}", message, traceStr);
                }

                if (MThread.isMainThread())
                {
                    this.logout(message, LogColor.eLC_LOG);
                }
                else
                {
                    this.asyncLog(message);
                }
            }
        }

        public void lua_warn(string message, int logTypeId = 0)
        {
            //this.warn(message, (LogTypeId)logTypeId);
            this.logout(string.Format("Lua-{0}", message), LogColor.eLC_WARN);
        }

        public void warn(string message, LogTypeId logTypeId = LogTypeId.eLogCommon)
        {
            if (isInFilter(logTypeId, LogColor.eLC_WARN))
            {
                if (this.mIsOutTimeStamp[(int)LogColor.eLC_WARN])
                {
                    message = string.Format("{0}: {1}", UtilSysLibWrap.getFormatTime(), message);
                }

                if (this.mIsOutStack[(int)LogColor.eLC_WARN])
                {
                    System.Diagnostics.StackTrace stackTrace = new System.Diagnostics.StackTrace(true);
                    string traceStr = stackTrace.ToString();
                    message = string.Format("{0}\n{1}", message, traceStr);
                }

                if (MThread.isMainThread())
                {
                    this.logout(message, LogColor.eLC_WARN);
                }
                else
                {
                    this.asyncWarn(message);
                }
            }
        }

        public void lua_error(string message, int logTypeId = 0)
        {
            //this.error(message, (LogTypeId)logTypeId);
            this.logout(string.Format("Lua-{0}", message), LogColor.eLC_ERROR);
        }

        public void error(string message, LogTypeId logTypeId = LogTypeId.eLogCommon)
        {
            if (isInFilter(logTypeId, LogColor.eLC_ERROR))
            {
                if (this.mIsOutTimeStamp[(int)LogColor.eLC_ERROR])
                {
                    message = string.Format("{0}: {1}", UtilSysLibWrap.getFormatTime(), message);
                }

                if (this.mIsOutStack[(int)LogColor.eLC_ERROR])
                {
                    System.Diagnostics.StackTrace stackTrace = new System.Diagnostics.StackTrace(true);
                    string traceStr = stackTrace.ToString();
                    message = string.Format("{0}\n{1}", message, traceStr);
                }

                if (MThread.isMainThread())
                {
                    this.logout(message, LogColor.eLC_ERROR);
                }
                else
                {
                    this.asyncError(message);
                }
            }
        }

        // 多线程日志
        protected void asyncLog(string message)
        {
            mAsyncLogList.add(message);
        }

        // 多线程日志
        protected void asyncWarn(string message)
        {
            this.mAsyncWarnList.add(message);
        }

        // 多线程日志
        protected void asyncError(string message)
        {
            this.mAsyncErrorList.add(message);
        }

        public void logout(string message, LogColor type = LogColor.eLC_LOG)
        {
            if (MacroDef.THREAD_CALLCHECK)
            {
                MThread.needMainThread();
            }

            int idx = 0;
            int len = this.mLogDeviceList.count();
            LogDeviceBase logDevice = null;

            while (idx < len)
            {
                logDevice = this.mLogDeviceList[idx];
                logDevice.logout(message, type);

                ++idx;
            }
        }

        public void updateLog()
        {
            if (MacroDef.THREAD_CALLCHECK)
            {
                MThread.needMainThread();
            }

            while ((this.mTmpStr = this.mAsyncLogList.removeAt(0)) != default(string))
            {
                this.logout(this.mTmpStr, LogColor.eLC_LOG);
            }

            while ((this.mTmpStr = this.mAsyncWarnList.removeAt(0)) != default(string))
            {
                this.logout(this.mTmpStr, LogColor.eLC_WARN);
            }

            while ((this.mTmpStr = this.mAsyncErrorList.removeAt(0)) != default(string))
            {
                this.logout(this.mTmpStr, LogColor.eLC_ERROR);
            }
        }

        protected void closeDevice()
        {
            foreach (LogDeviceBase logDevice in mLogDeviceList.list())
            {
                logDevice.closeDevice();
            }
        }
    }
}
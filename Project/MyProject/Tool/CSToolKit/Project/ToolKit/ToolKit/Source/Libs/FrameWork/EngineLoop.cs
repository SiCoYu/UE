namespace SDK.Lib
{
    /**
     * @brief 主循环
     */
    public class EngineLoop
    {
        protected bool mIsLoop;

        public EngineLoop()
        {
            this.mIsLoop = true;
        }

        public void init()
        {

        }

        public void dispose()
        {

        }

        public bool isLoop()
        {
            return this.mIsLoop;
        }

        public void setIsLoop(bool value)
        {
            this.mIsLoop = value;
        }

        protected void _mainLoopImpl()
        {
            // 时间间隔
            Ctx.msInstance.mSystemTimeData.nextFrame();

            // 每一帧处理
            // 处理 input
            //Ctx.msInstance.mInputMgr.handleKeyBoard();

            // 处理客户端的各类消息
            // 处理客户端自己的消息机制

            MsgRouteBase routeMsg = null;

            while ((routeMsg = Ctx.msInstance.mSysMsgRoute.popMsg()) != null)
            {
                Ctx.msInstance.mMsgRouteNotify.handleMsg(routeMsg);
            }

            // 处理网络
            //if (!Ctx.msInstance.mNetCmdNotify.isStopNetHandle)
            //{
            //    MByteBuffer ret = null;
            //    while ((ret = Ctx.msInstance.mNetMgr.getMsg()) != null)
            //    {
            //        if (null != Ctx.msInstance.mNetCmdNotify)
            //        {
            //            Ctx.msInstance.mNetCmdNotify.addOneHandleMsg();
            //            Ctx.msInstance.mNetCmdNotify.handleMsg(ret);       // CS 中处理
            //            Ctx.msInstance.mLuaSystem.receiveToLuaRpc(ret);    // Lua 中处理
            //        }
            //    }
            //}

            // 填充数据到 KBEngine ，使用 KBEngine 引擎的逻辑解析
            //if (!Ctx.msInstance.mNetCmdNotify.isStopNetHandle)
            //{
            //    MByteBuffer ret = null;
            //    while ((ret = Ctx.msInstance.mNetMgr.getMsg_KBE()) != null)
            //    {
            //        Ctx.msInstance.mMKBEMainEntry.gameapp.pushBuffer(ret.dynBuffer.buffer, ret.dynBuffer.size);
            //    }
            //}

            // KBEngine 引擎逻辑处理
            //Ctx.msInstance.mMKBEMainEntry.FixedUpdate();

            // 每一帧的游戏逻辑处理
            Ctx.msInstance.mProcessSys.processNextFrame();
            // 日志处理
            Ctx.msInstance.mLogSys.updateLog();
        }

        public void mainLoop()
        {
            if(MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("EngineLoop::MainLoop");
            }

            if(this.mIsLoop)
            {
                this._mainLoopImpl();
            }

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("EngineLoop::MainLoop");
            }
        }

        public void fixedUpdate()
        {
            if (this.mIsLoop)
            {
                Ctx.msInstance.mProcessSys.processNextFixedFrame();
            }
        }

        // 循环执行完成后，再次
        public void postUpdate()
        {
            if (this.mIsLoop)
            {
                Ctx.msInstance.mProcessSys.processNextLateFrame();
            }
        }
    }
}

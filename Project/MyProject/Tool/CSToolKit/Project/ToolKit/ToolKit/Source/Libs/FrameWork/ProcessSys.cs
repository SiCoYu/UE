/**
 * @brief 系统循环
 */
namespace SDK.Lib
{
    public class ProcessSys
    {
        public ProcessSys()
        {

        }

        public void init()
        {

        }

        public void dispose()
        {

        }

        public void processNextFrame()
        {
            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("ProcessSys::ProcessNextFrame");
            }

            //Ctx.msInstance.mSystemTimeData.nextFrame();
            this.advance(Ctx.msInstance.mSystemTimeData.getDeltaSec());

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("ProcessSys::ProcessNextFrame");
            }
        }

        public void advance(float delta)
        {
            Ctx.msInstance.mSystemFrameData.nextFrame(delta);

            Ctx.msInstance.mTickMgr.advance(delta, TickMode.eTM_Update);            // 心跳
            Ctx.msInstance.mTimerMgr.advance(delta);           // 定时器
            Ctx.msInstance.mFrameTimerMgr.advance(delta);      // 帧定时器
        }

        public void processNextFixedFrame()
        {
            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("ProcessSys::ProcessNextFixedFrame");
            }

            this.fixedAdvance(Ctx.msInstance.mSystemTimeData.getFixedTimestep());

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("ProcessSys::ProcessNextFixedFrame");
            }
        }

        public void fixedAdvance(float delta)
        {
            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("ProcessSys::FixedAdvance");
            }

            Ctx.msInstance.mFixedTickMgr.advance(delta, TickMode.eTM_FixedUpdate);

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("ProcessSys::FixedAdvance");
            }
        }

        public void processNextLateFrame()
        {
            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("ProcessSys::ProcessNextLateFrame");
            }

            this.lateAdvance(Ctx.msInstance.mSystemTimeData.getDeltaSec());

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("ProcessSys::ProcessNextLateFrame");
            }
        }

        public void lateAdvance(float delta)
        {
            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.enter("ProcessSys::LateAdvance");
            }

            Ctx.msInstance.mLateTickMgr.advance(delta, TickMode.eTM_LateUpdate);

            if (MacroDef.ENABLE_PROFILE)
            {
                Ctx.msInstance.mProfiler.exit("ProcessSys::LateAdvance");
            }
        }
    }
}
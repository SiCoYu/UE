namespace SDK.Lib
{
    /**
     * @brief 系统事件
     */
    public class SystemEvent : IDispatchObject, ICalleeObject
    {
        protected AddOnceEventDispatch[] mEventDispatchArray;
        protected bool mCurHasFocus;
        protected bool mCurPauseStatus;

        public SystemEvent()
        {
            this.mEventDispatchArray = new AddOnceEventDispatch[(int)SystemEventId.eSEI_Total];
            this.mCurHasFocus = true;
            this.mCurPauseStatus = false;
        }

        public void call(IDispatchObject dispObj, uint uniqueId)
        {

        }

        public void init()
        {
            this.addSystemEventHandle(SystemEventId.eSEI_FOCUS, this, this.onFocusChangeHandle);
        }

        public void dispose()
        {
            int index = 0;
            int listLen = this.mEventDispatchArray.Length;

            while(index < listLen)
            {
                if(null != this.mEventDispatchArray[index])
                {
                    this.mEventDispatchArray[index].clearEventHandle();
                    this.mEventDispatchArray[index] = null;
                }

                index += 1;
            }

            this.mEventDispatchArray = null;
        }

        public bool hasFocus()
        {
            return this.mCurHasFocus;
        }

        public void setHasFocus(bool value)
        {
            this.mCurHasFocus = value;
        }

        public void setPauseState(bool value)
        {
            this.mCurPauseStatus = value;
        }

        public bool isPauseState()
        {
            return this.mCurPauseStatus;
        }

        public void addSystemEventHandle(SystemEventId systemEventId, ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
        {
            if(null == this.mEventDispatchArray[(int)systemEventId])
            {
                this.mEventDispatchArray[(int)systemEventId] = new AddOnceEventDispatch();
            }

            this.mEventDispatchArray[(int)systemEventId].addEventHandle(pThis, handle);
        }

        public void removeSystemEventHandle(SystemEventId systemEventId, ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
        {
            if(null != this.mEventDispatchArray[(int)systemEventId])
            {
                this.mEventDispatchArray[(int)systemEventId].removeEventHandle(pThis, handle);
            }
        }

        public void dispatchSystemEvent(SystemEventId systemEventId)
        {
            if (null != this.mEventDispatchArray[(int)systemEventId])
            {
                this.mEventDispatchArray[(int)systemEventId].dispatchEvent(this);
            }
        }

        protected void onFocusChangeHandle(IDispatchObject dispObj, uint uniqueId)
        {
            if (this.mCurHasFocus)
            {
                Ctx.msInstance.mSystemFrameData.setGetFocusFrameCount(Ctx.msInstance.mSystemFrameData.getTotalFrameCount());

                // 获取焦点就正常帧数
                //UtilEngineWrap.setTargetFrameRate(24);
            }
            else
            {
                Ctx.msInstance.mSystemFrameData.setLostFocusFrameCount(Ctx.msInstance.mSystemFrameData.getTotalFrameCount());

                // 失去焦点就降低帧数
                //if (MacroDef.MOBILE_PLATFORM)
                //    UtilEngineWrap.setTargetFrameRate(1);
            }

            if (MacroDef.MOBILE_PLATFORM)
                Ctx.msInstance.mEngineLoop.setIsLoop(this.mCurHasFocus);

            if(MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("SystemEvent::onFocusChangeHandle, CurHasFocus = {0}", this.mCurHasFocus.ToString()), LogTypeId.eLogWinFocus);
            }
        }
    }
}
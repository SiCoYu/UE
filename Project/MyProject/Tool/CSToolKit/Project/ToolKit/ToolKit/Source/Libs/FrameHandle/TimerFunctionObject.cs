namespace SDK.Lib
{
    public class TimerFunctionObject
    {
        protected ICalleeObject mThis;
        protected MEventDispatchAction<TimerItemBase> mHandle;
        protected uint mEventId;

        public TimerFunctionObject()
        {
            this.mThis = null;
            this.mHandle = null;
            this.mEventId = 0;
        }

        public void setFuncObject(ICalleeObject pThis, MEventDispatchAction<TimerItemBase> handle, uint eventId)
        {
            this.mHandle = handle;
            this.mEventId = eventId;
        }

        public bool isValid()
        {
            return this.mHandle != null;
        }

        public bool isEventIdEqual(uint eventId)
        {
            return this.mEventId == eventId;
        }

        public bool isEqual(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            bool ret = false;

            if (pThis != null)
            {
                ret = UtilSysLibWrap.isAddressEqual(this.mThis, pThis);

                if (!ret)
                {
                    return ret;
                }
            }

            if (handle != null)
            {
                ret = UtilSysLibWrap.isAddressEqual(this.mHandle, handle);

                if (!ret)
                {
                    return ret;
                }
            }

            if (pThis != null || handle != null)
            {
                ret = this.isEventIdEqual(eventId);

                if (!ret)
                {
                    return ret;
                }
            }

            return ret;
        }

        public void call(TimerItemBase dispObj)
        {
            if (null != this.mHandle)
            {
                this.mHandle(dispObj, this.mEventId);
            }
        }
    }
}
namespace SDK.Lib
{
    public class EventDispatchFunctionObject : GObject, INoOrPriorityObject
    {
        public ICalleeObject mThis;
        public MEventDispatchAction<IDispatchObject> mHandle;
        public uint mEventId;   // 事件唯一 Id

        public EventDispatchFunctionObject()
        {
            
        }

        public void setFuncObject(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> function, uint eventId = 0)
        {
            this.mThis = pThis;
            this.mHandle = function;
            this.mEventId = eventId;
        }

        public bool isValid()
        {
            return (this.mThis != null || this.mHandle != null);
        }

        public bool isEventIdEqual(uint eventId)
        {
            return this.mEventId == eventId;
        }

        public bool isEqual(
            ICalleeObject pThis,
            MEventDispatchAction<IDispatchObject> handle,
            uint eventId
            )
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
                //ret = UtilEngineWrap.isAddressEqual(this.mHandle, handle);
                ret = UtilSysLibWrap.isDelegateEqual(ref this.mHandle, ref handle);

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

        public void clear()
        {
            this.clearFuncObject();
        }

        public bool empty()
        {
            return !this.isValid();
        }

        public void clearFuncObject()
        {
            this.mThis = null;
            this.mHandle = null;
            this.mEventId = 0;
        }

        public void call(IDispatchObject dispObj)
        {
            if (null != this.mHandle)
            {
                this.mHandle(dispObj, this.mEventId);
            }
        }
    }
}
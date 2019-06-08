namespace SDK.Lib
{
    public class AddOnceAndCallOnceEventDispatch : EventDispatch
    {
        override public void addEventHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId = 0)
        {
            if (!this.isExistEventHandle(pThis, handle, eventId))
            {
                base.addEventHandle(pThis, handle, eventId);
            }
        }

        override public void dispatchEvent(IDispatchObject dispatchObject)
        {
            base.dispatchEvent(dispatchObject);

            this.clearEventHandle();
        }
    }
}
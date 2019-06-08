namespace SDK.Lib
{
    public class AuxPropertyBase : IDispatchObject
    {
        protected bool mIsValid;
        protected AddOnceEventDispatch mValueChangedEventDispatch;

        public AuxPropertyBase()
        {
            this.mIsValid = false;
            this.mValueChangedEventDispatch = null;
        }

        virtual public void init()
        {

        }

        virtual public void dispose()
        {

        }

        public void setIsValid(bool value)
        {
            this.mIsValid = value;
        }

        public bool isValid()
        {
            return this.mIsValid;
        }

        virtual public void setBoolValue(bool value)
        {
            this.onValueChanged();
        }

        virtual public bool getBoolValue()
        {
            return false;
        }

        virtual public void setIntValue(int value)
        {
            this.onValueChanged();
        }

        virtual public int getIntValue()
        {
            return 0;
        }

        virtual public void setFloatValue(float value)
        {
            this.onValueChanged();
        }

        virtual public float getFloatValue()
        {
            return 0;
        }

        virtual public void setStrValue(string value)
        {
            this.onValueChanged();
        }

        virtual public string getStrValue()
        {
            return "";
        }

        virtual public string toStrValue()
        {
            return "";
        }

        // ÖµÐÞ¸Ä
        public void onValueChanged()
        {
            this.mIsValid = true;

            if (null != this.mValueChangedEventDispatch)
            {
                this.mValueChangedEventDispatch.dispatchEvent(this);
            }
        }

        public void addValueChangedEventHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            if (null == this.mValueChangedEventDispatch)
            {
                this.mValueChangedEventDispatch = new AddOnceEventDispatch();
            }

            this.mValueChangedEventDispatch.addEventHandle(pThis, handle, eventId);
        }

        public void clearValueChangedEventHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            if (null != this.mValueChangedEventDispatch)
            {
                this.mValueChangedEventDispatch.removeEventHandle(pThis, handle, eventId);
            }
        }
    }
}
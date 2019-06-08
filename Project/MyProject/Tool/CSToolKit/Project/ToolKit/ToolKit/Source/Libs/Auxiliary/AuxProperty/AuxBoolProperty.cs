namespace SDK.Lib
{
    public class AuxBoolProperty : AuxPropertyBase
    {
        protected bool mValue;

        public AuxBoolProperty()
        {
            this.mValue = false;
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        override public void setBoolValue(bool value)
        {
            this.mValue = value;

            base.setBoolValue(value);
        }

        override public bool getBoolValue()
        {
            return this.mValue;
        }

        override public string toStrValue()
        {
            return "";
        }
    }
}
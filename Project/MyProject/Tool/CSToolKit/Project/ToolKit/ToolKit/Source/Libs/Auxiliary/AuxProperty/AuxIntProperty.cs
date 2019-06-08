namespace SDK.Lib
{
    public class AuxIntProperty : AuxPropertyBase
    {
        protected int mValue;

        public AuxIntProperty()
        {
            this.mValue = 0;
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        override public void setIntValue(int value)
        {
            this.mValue = value;

            base.setIntValue(value);
        }

        override public int getIntValue()
        {
            return this.mValue;
        }

        override public string toStrValue()
        {
            return MBitConverter.toString((ulong)this.mValue);
        }
    }
}
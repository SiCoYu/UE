namespace SDK.Lib
{
    public class AuxStrProperty : AuxPropertyBase
    {
        protected string mValue;

        public AuxStrProperty()
        {
            this.mValue = "";
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        override public void setStrValue(string value)
        {
            this.mValue = value;

            base.setStrValue(value);
        }

        override public string getStrValue()
        {
            return this.mValue;
        }

        override public string toStrValue()
        {
            return this.mValue;
        }
    }
}
namespace SDK.Lib
{
    public class AuxFloatProperty : AuxPropertyBase
    {
        protected float mValue;

        public AuxFloatProperty()
        {
            this.mValue = 0;
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        override public void setFloatValue(float value)
        {
            this.mValue = value;

            base.setFloatValue(value);
        }

        override public float getFloatValue()
        {
            return this.mValue;
        }
    }
}